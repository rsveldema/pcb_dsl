#if SUPPORT_OPENCL

#include <algorithm>
#include <thread>
#include <string.h>
#include <boost/algorithm/string/replace.hpp>

#include "optimizer.hpp"
#include "create_model.hpp"
#include "utils.hpp"
#include "mustache.hpp"
#include <iostream>

#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

std::string slurp(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (!fp)
	{
		fprintf(stderr, "failed to open file '%s'\n", filename);
		abort();
	}
	std::string ret;
	char buf[1025];
	while (!feof(fp))
	{
		int a = fread(buf, 1, sizeof(buf) - 1, fp);
		buf[a] = 0;
		ret += buf;
	}
	fclose(fp);
	return ret;
}

cl::Device init_opencl()
{
	// get all platforms (drivers), e.g. NVIDIA
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);

	if (all_platforms.size() == 0) {
		std::cout << " No platforms found. Check OpenCL installation!\n";
		abort();
	}
	bool set = false;
	cl::Device default_device;
	for (auto p : all_platforms) {
		cl::Platform default_platform = p;
		std::cout << "Using platform: " << p.getInfo<CL_PLATFORM_NAME>() << "\n";

		// get default device (CPUs, GPUs) of the default platform
		std::vector<cl::Device> all_devices;
		default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
		if (all_devices.size() == 0) {
			std::cout << " No devices found. Check OpenCL installation!\n";
			abort();
		}

		for (auto d : all_devices)
		{
			std::cout << "Test Device: " << d.getInfo<CL_DEVICE_NAME>() << "\n";
		}

		if (!set) {
			set = true;
			// use device[1] because that's a GPU; device[0] is the CPU
			default_device = all_devices[all_devices.size() - 1];
			std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";
		}
	}
	return default_device;
}

std::string get_name(Component *c)
{
	std::string ret = c->info->name;
	if (ret == "router")
	{
		char buf[32];
		sprintf(buf, "router_%d", c->id);
		return buf;
	}
	return ret;
}

std::string get_name(Pin *c)
{
	std::string pin_name = get_name(c->component);
	pin_name += "_";
	pin_name += c->info->name;
	return pin_name;
}

std::string create_opencl_datastructure(Model *model)
{
	std::string ret;

	ret += "// forward declare pins and components:\n";
	for (auto c : model->components)
	{
		std::string component_name = get_name(c);
		ret += "struct COMPONENT_" + component_name + ";\n";
		for (auto p : c->pins)
		{
			auto pin_name = get_name(p);
			ret += "struct PIN_" + pin_name + ";\n";
		}
	}
	ret += "\n";

	ret += "// declare pins:\n";
	for (auto c : model->components)
	{
		std::string component_name = get_name(c);
		for (auto p : c->pins)
		{
			auto pin_name = get_name(p);
			ret += "struct PIN_" + pin_name + " {\n";
			ret += "\tOutline outline;\n";
			ret += "\tstruct COMPONENT_" + component_name + "* parent;\n";
			for (unsigned i = 0; i < p->size(); i++)
			{
				auto to_pin = p->get(i);
				auto to_name = get_name(to_pin);
				ret += "\tstruct PIN_" + to_name + " *CONN_" + to_name + ";\n";
			}
			ret += "};\n";
		}
	}

	ret += "// declare component:\n";
	for (auto c : model->components)
	{
		std::string component_name = get_name(c);
		ret += "struct COMPONENT_" + component_name + " {\n";
		ret += "\tOutline outline;\n";
		ret += "\tOutline bounding_box;\n";
		ret += "\tComponentInfo *info;\n";
		for (auto p : c->pins)
		{
			auto pin_name = get_name(p);
			ret += "\tstruct PIN_" + pin_name + " " + pin_name + ";\n";
		}
		ret += "};\n";
	}
	ret += "\n";

	ret += "typedef struct Model {\n";
	for (auto c : model->components)
	{
		std::string component_name = get_name(c);
		ret += "\tstruct COMPONENT_" + component_name + " " + component_name + ";\n";
	}
	ret += "} Model;\n";
	return ret;
}

std::string gen_assign(const std::string &base, const Point &p)
{
	std::string ret;
	ret += utils::str("\t", base + ".x = ", p.x, ";\n");
	ret += utils::str("\t", base + ".y = ", p.y, ";\n");
	ret += utils::str("\t", base + ".layer = ", p.get_layer(), ";\n");
	return ret;
}

std::string generate_outline(std::string &base, const Outline &outline)
{
	std::string ret;
	for (int i = 0; i < outline.size(); i++)
	{
		auto point = outline.get(i);
		ret += gen_assign(utils::str(base, "p[", i, "]"), point);
	}
	return ret;
}

std::string create_model_info_code(Model *model)
{
	std::string ret;
	for (auto c : model->components)
	{
		std::string component_name = get_name(c);
		ret += "model->" + component_name + ".info = &info->" + component_name + ";\n";
		ret += generate_outline(utils::str("model->" + component_name + ".bounding_box."), c->bounding_box);
		ret += generate_outline(utils::str("model->" + component_name + ".outline."), c->bounding_box);
		for (auto p : c->pins)
		{
			auto pin_name = get_name(p);
			ret += generate_outline(utils::str("model->" + component_name + "." + pin_name + ".outline."), p->outline);

			for (unsigned i = 0; i < p->size(); i++)
			{
				auto to_pin = p->get(i);
				auto to_name = get_name(to_pin);

				auto to_comp = to_pin->component;
				auto to_comp_name = get_name(to_comp);

				ret += utils::str(
					"model->" + component_name + "." + pin_name + ".CONN_" + to_name + " = &",
					"model->" + to_comp_name + "." + to_name + ";\n");
			}
		}
	}
	return ret;
}

std::string create_model_info_data(Model *model)
{
	std::string ret;
	for (auto c : model->components)
	{
		ret += "\tComponentInfo " + get_name(c) + ";\n";
	}
	return ret;
}

std::string generate_sourcecode(Model *model)
{
	std::string input = slurp("opencl/template.opencl.c");
	using namespace kainjow::mustache;
	mustache tmpl(input);

	std::string datastructure = create_opencl_datastructure(model);
	std::string model_info_code = create_model_info_code(model);
	std::string model_info_data = create_model_info_data(model);

	data data;
	data.set("DATASTRUCTURE", datastructure);
	data.set("LINK_MODEL", model_info_code);
	data.set("COMPONENT_INFO_DATASTRUCTURE", model_info_data);

	tmpl.set_custom_escape([](const std::string& s) {
		std::string ret; ret.reserve(s.size());
		for (const auto ch : s) {
			switch (ch) {
			case '\"':
			case '\n':
				ret.append({ ' ', ch });
				break;
			default:
				ret.append(1, ch);
				break;
			}
		}
		return ret;
	});
	std::string result = tmpl.render(data);

	FILE *output = fopen("opencl/output.c", "w");
	assert(output);
	fwrite(result.c_str(), 1, result.size(), output);
	fclose(output);

	return result;
}

#define OCL_CHECK_ERRORS(err) { \
if (err != 0) { \
	fprintf(stderr, "%d:%s: openCL error: %d\n", __LINE__, __FILE__, err); \
	abort(); \
} \
}




Model* opencl_optimize_model(Model *model,
	unsigned time_limit_secs,
	bool enable_gui,
	InitialPlacement initial_placement)
{
	auto source = generate_sourcecode(model);
	auto device = init_opencl();

	cl::Context ctxt(device);

	cl::Program program(ctxt, source);

	cl_int err = program.build();
	OCL_CHECK_ERRORS(err);

	std::vector<cl::Kernel> kernels;
	program.createKernels(&kernels);

	cl::CommandQueue queue;

	//kernels.at(0).getInfo()
	//queue.enqueueCopyBuffer()

	return model;
}

#endif