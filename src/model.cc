#include "create_model.h"
#include "utils.h"

static float WIRE_WIDTH = 0.1;


ComponentInfo::ComponentInfo(const std::string &_name, bool _is_router)
  : dim(0, 0, 0),
    fixed_position(NULL),
    name(_name),    
    is_router(_is_router),
    is_board(_name == "board")
{
  if (is_router)
    {
      component_type = "router";
      dim.x = WIRE_WIDTH;
      dim.y = WIRE_WIDTH;
    }
}


Pin *Pin::shallow_clone(Component *comp, clone_map_t &map)
{
  auto c = new Pin(info, comp);
  c->id = this->id;
  c->outline = this->outline;
  return c;
}


Component *Component::shallow_clone(Model *m, clone_map_t &map)
{
  auto c = new Component(info, m);
  c->id = id;  
  c->outline = this->outline;

  const unsigned count = pins.size();
  for (unsigned i=0;i<count;i++)
    {
      auto p = pins[i];
      auto cloned_pin = p->shallow_clone(c, map);
      c->pins.push_back(cloned_pin);
    }    
  map[this] = c;
  return c;
}


static PinInfo *router_in = new PinInfo("in");
static PinInfo *router_out = new PinInfo("out");
static ComponentInfo *router_info = new ComponentInfo("router", true);

Component *Model::create_router(const Point &pos)
{
  //#print("creating router")
  auto comp = new Component(router_info, this);
  components.push_back(comp);
  auto pin_in  = comp->add_pin(router_in);
  auto pin_out = comp->add_pin(router_out);
  
  auto s = Point(0, 0, 0);
  auto e = s.add(comp->info->dim);

  comp->outline.addRect(s, e);
  pin_in->outline.addRect(s, e);
  pin_out->outline.addRect(s, e);

  comp->transpose( pos );
  return comp;
}

Pin *Component::find_pin_by_id(unsigned id) const
{
  const unsigned count = pins.size();
  for (unsigned i=0;i<count;i++)
    {
      auto p = pins[i];
      if (p->id == id)
	{
	  return p;
	}
    }
  
  abort();
  return NULL;
}


void Pin::relink(Pin *orig, clone_map_t &map)
{
  //#print("adding connections for " + str(len(orig.connections)))
  const unsigned count = orig->connections.size();
  for (unsigned i=0;i<count;i++)
    {
      auto p = orig->connections[i];
      auto new_comp = map[p->component];
      auto new_pin = new_comp->find_pin_by_id(p->id);
      connections.push_back(new_pin);
    }
}

void Component::relink(Model *m, clone_map_t &map)
{  
  auto c = map[this];
  const unsigned count = pins.size();
  for (unsigned ix = 0; ix < count; ix++)
    {
      auto orig = pins[ix];
      auto clone = c->pins[ix];
      clone->relink(orig, map);
    }
}


Model *Model::deepclone()
{
  auto m = new Model();
  m->constants = constants;
  m->board_dim = board_dim;

  clone_map_t map;

  const unsigned count = components.size();
  for (unsigned i=0;i<count;i++)
    {
      auto comp = components[i];
      auto c = comp->shallow_clone(m, map);
      m->components.push_back(c);
    }

  //const unsigned count = components.size();
  for (unsigned i=0;i<count;i++)
    {
      auto comp = components[i];
      comp->relink(m, map);
    }
  return m;
}


Pin *Component::get_pin_by_suffixes(const std::vector<dslParser::Access_suffixContext*> &suffixes,
				    ModelContext &context, bool odd)
{
  if (suffixes.size() == 0) {
    if (this->pins.size() == 1) {
      return this->pins[0];
    }
    
    if (this->pins.size() > 2) {
      printf("don't know which pin to address, please make it explicit: %s\n", this->info->name.c_str());
      abort();
    }
    
    return this->pins[odd];

  } else {
    auto s0 = suffixes[0];
    auto name = s0->ID()->getText();
    if (s0->index() == 0)
      return this->get_pin_by_name(name);
    else
      return this->get_pin_by_name(context.indexed_pin_name(name, s0->index()));
  }
}


void Model::writeDOT(const std::string filename)
{
    FILE *f = fopen(filename.c_str(), "w");
    assert(f != NULL);

    fprintf(f, "digraph model {\n");
    for (auto c : components)
      {
	for (auto p : c->pins)
	  {
	    std::string from = c->info->name + "_" + p->info->name;

	    fprintf(f, "%s -> %s;\n", c->info->name.c_str(), from.c_str());	    
	    fprintf(f, "%s [label=\"%s @ %d\"];\n", from.c_str(), from.c_str(), p->get_layer());
	    for (auto to_pin : p->connections)
	      {
		std::string to = to_pin->component->info->name + "_" + to_pin->info->name;
		
		fprintf(f, "%s -> %s;\n", from.c_str(), to.c_str());
	      }
	  }
      }

    fprintf(f, "}\n");
    fclose(f);
}


