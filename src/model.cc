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
  auto m = new Model(info);

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


