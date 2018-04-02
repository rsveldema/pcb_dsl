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
using namespace kainjow::mustache;

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

std::string Model::create_opencl_datastructure()
{
	std::string ret;
	
	ret += "// forward declare pins and components:\n";
	for (auto c : components)
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
	for (auto c : components)
	{
		std::string component_name = get_name(c);
		for (auto p : c->pins)
		{
			auto pin_name = get_name(p);
			ret += "struct PIN_" + pin_name + " {\n";
			ret += "\tOutline outline;\n";
			ret += "\tstruct COMPONENT_" + component_name + "* parent;\n";
			for (unsigned i=0;i<p->size();i++)
			{
				auto to_pin = p->get(i);
				auto to_name = get_name(to_pin);
				ret += "\tstruct PIN_" + to_name  + " *CONN_" + to_name + ";\n";
			}
			ret += "};\n";
		}
	}

	ret += "// declare component:\n";
	for (auto c : components)
	{
		std::string component_name = get_name(c);
		ret += "struct COMPONENT_" + component_name + " {\n";
		ret += "\tOutline outline;\n";
		ret += "\tOutline bounding_box;\n";
		for (auto p : c->pins)
		{
			auto pin_name = get_name(p);
			ret += "\tstruct PIN_" + pin_name + " " + pin_name + ";\n";
		}
		ret += "};\n";
	}
	ret += "\n";

	ret += "typedef struct Model {\n";
	for (auto c : components)
	{
		std::string component_name = get_name(c);
		ret += "\tstruct COMPONENT_" + component_name + " " + component_name + ";\n";
	}
	ret += "} Model;\n";
	return ret; 
}


std::string generate_program(Model *model)
{
	std::string input = slurp("opencl/template.opencl.c");
	mustache tmpl(input);

	std::string datastructure = model->create_opencl_datastructure();
	data data;
	data.set("DATASTRUCTURE", datastructure);
	std::string result = tmpl.render(data);

	FILE *output = fopen("opencl/output.c", "w");
	assert(output);
	fwrite(result.c_str(), 1, result.size(), output);
	fclose(output);
	
	return result;
}

Model* opencl_optimize_model(Model *model,
	unsigned time_limit_secs,
	bool enable_gui,
	InitialPlacement initial_placement)
{
	auto program = generate_program(model);
	auto device = init_opencl();

	return model;
}

#endif