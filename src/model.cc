#include "create_model.h"
#include <boost/algorithm/string/replace.hpp>
#include "utils.h"

unsigned get_unique_id()
{
  static unsigned id;
  return id++;
}

std::string normalize(const std::string &str)
{
  std::string s(str);
  boost::replace_all(s, "-", "_");
  boost::replace_all(s, " ", "_");
  return s;
}

Pin *Pin::shallow_clone(Component *comp, clone_map_t &map)
{
  auto c = new Pin(comp, this->name);
  c->description = this->description;
  c->mode = this->mode;
  c->id = this->id;
  c->outline = this->outline;
  return c;
}


Component *Component::shallow_clone(Model *m, clone_map_t &map)
{
  auto c = new Component(m, name, is_router);
  c->fixed_position = fixed_position;
  c->dim = dim;
  c->component_type = component_type;
  c->id = id;  
  c->pkg_list = this->pkg_list;
  c->table_list = this->table_list;
  c->has_data_sheet = this->has_data_sheet;
  c->outline = this->outline;
  
  for (auto p : pins)
    {
      auto cloned_pin = p->shallow_clone(c, map);
      c->pins.push_back(cloned_pin);
    }    
  map[this] = c;
  return c;
}

std::string get_new_routing_name()
{
  return utils::str("route_", get_unique_id());
}

Component *Model::create_router(const Point &pos)
{
  //#print("creating router")
  auto comp = new Component(this, get_new_routing_name(), true);
  comp->component_type = "router";
  comp->dim.x  = this->WIRE_WIDTH;
  comp->dim.y = this->WIRE_WIDTH;
  components.push_back(comp);
  auto pin_in  = comp->add_pin("in");
  auto pin_out = comp->add_pin("out");
  
  auto s = Point(0, 0, 0);
  auto e = s.add(comp->dim);

  comp->outline.addRect(s, e);
  pin_in->outline.addRect(s, e);
  pin_out->outline.addRect(s, e);

  comp->transpose( pos );
  return comp;
}

void Pin::relink(Pin *orig, clone_map_t &map)
{
  //#print("adding connections for " + str(len(orig.connections)))
  for (auto p : orig->connections)
    {
      auto new_comp = map[p->component];
      auto new_pin = new_comp->find_pin_by_id(p->id);
      connections.push_back(new_pin);
    }
}

void Component::relink(Model *m, clone_map_t &map)
{  
  auto c = map[this];
  for (unsigned ix = 0; ix < pins.size(); ix++)
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
    
  for (auto comp : components)
    {
      auto c = comp->shallow_clone(m, map);
      m->components.push_back(c);
    }
        
  for (auto comp : components)
    {
      comp->relink(m, map);
    }
  return m;
}


bool valid_pin_name(const std::string &name)
{
  if (name == "Name") {
    return false;
  }
  return true;
}
    

Pin *Component::get_pin_by_suffixes(const std::vector<dslParser::Access_suffixContext*> &suffixes,
				    ModelContext &context, bool odd)
{
  if (suffixes.size() == 0) {
    if (this->pins.size() == 1) {
      return this->pins[0];
    }
    
    if (this->pins.size() > 2) {
      printf("don't know which pin to address, please make it explicit: %s\n", this->name.c_str());
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
