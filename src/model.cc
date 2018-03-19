#include "create_model.h"
#include "utils.h"
#include <math.h>
#include <cmath>

static float WIRE_WIDTH = 0.1;

/** returns angles in degrees (not radians)
 */
std::pair<double,double> Component::get_connection_angle_info(InMap &in_map)
{
  assert(pins.size() == 2);
  
  Pin *my_from_pin = pins[0];
  Pin *my_to_pin   = pins[1];

  bool found = false;
  double min_angle = 0;
  double max_angle = 0;

  assert(in_map.get_in(my_from_pin).size() > 0);
  assert(my_to_pin->connections.size() > 0);
  
  for (auto in : in_map.get_in(my_from_pin))
    {
      for (auto out : my_to_pin->connections)
	{
	  if (out->overlaps(in) ||
	      in->overlaps(out))
	    {
	      continue;
	    }
	  
	  assert(in != out);
	  assert(my_from_pin != in);
	  assert(my_to_pin != in);
	  assert(my_from_pin != out);
	  assert(my_to_pin != out);
	  
	  Point p3 = center();
	  Point p1 = in->center();
	  Point p2 = out->center();

	  Point v1 = p1.sub(p3);
	  Point v2 = p2.sub(p3);

	  double angleA = atan2(v2.y, v2.x) - atan2(v1.y, v1.x);
	  
	  angleA /= M_PI;
	  int angle = angleA * 180.0;
	  angle %= 360;
	  angle = abs(angle);
	  
	  if (!found)
	    {
	      found = true;
	      max_angle = min_angle = angle;
	    }
	  else
	    {
	      max_angle = std::max(max_angle, (double)angle);
	      min_angle = std::min(min_angle, (double)angle);
	    }
	}
    }
  assert(found);
  return {min_angle, max_angle};
}

unsigned Model::get_num_sharp_angles()
{
  unsigned sharp_angles = 0;
  const unsigned num_comp = components.size();

  InMap in_map(this);
  
  for (unsigned i=0;i<num_comp;i++)
    {
      auto c = components[i];
      if (c->info->is_router)
	{
	  std::pair<double,double> angle_info = c->get_connection_angle_info(in_map);

	  auto min = std::abs(angle_info.first);
	  auto max = std::abs(angle_info.second);

	  //min = min % 180;
	  //max = max % 180;
	  	  
	  //printf("angle computed = %d - %d\n", min, max);
	  if (min > 0 && min < 45)
	    {
	      sharp_angles++;
	    }
	  else if (max > 0 && max < 45)
	    {
	      sharp_angles++;
	    }
	}
    }
			    
  return sharp_angles;
}



ComponentInfo::ComponentInfo(const std::string &_name, bool _is_router)
  : fixed_position(NULL),
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
  auto c = new Pin(info, comp, outline);
  return c;
}


Component *Component::shallow_clone(Model *m, clone_map_t &map)
{
  auto c = new Component(info, m, id, outline, bounding_box);
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
      if (p->info->id == id)
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
      auto new_pin = new_comp->find_pin_by_id(p->info->id);
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


