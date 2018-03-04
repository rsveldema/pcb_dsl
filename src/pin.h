#ifndef PIN_H__H_H__
#define PIN_H__H_H__

class Pin;

struct Connection
{
  Pin *from, *to;
  Point p1, p2, conflict;

  bool crosses(const Connection &connection);
};

#include "layer_map.h"

/** holds info shared by all instances of a given pin type.
 */
class PinInfo
{
 public:
  enum class Mode
  {
    INPUT, OUTPUT, INOUT, DIGITAL_GROUND, ANALOG_GROUND,
  } mode;
  
  std::string name;
  std::string description;

  PinInfo(const std::string &_name)
    : name(_name)
  {
  }
};

class Pin
{
 public:
  PinInfo *info;
  unsigned id;
  Component *component;
  Outline outline;
  std::vector<Pin *> connections;

 public:
 Pin(PinInfo *_info,
     Component *comp)
   : info(_info),
    id(get_unique_id()),
    component(comp)
    {
    }

  std::string str() const
    {
      std::string ret = info->name;
      ret += "(";
      ret += outline.str();
      ret += ")";
      return ret;
    }

  void check()
  {
    if (outline.size() == 0)
      {
	fprintf(stderr, "ERROR: pin %s has no outline\n", info->name.c_str());
	abort();
      }
  }
  
  layer_t get_layer() const { return outline.get_layer(); }
  void gather_layer_map(LayerMap &map);
  bool have_crossing_connection(const Connection &connection,
				Connection *crossed);
  void route_around_conflict(Model *model,
			     Component *comp,
			     const Point &around);
  bool add_layers_for_crossing_lines(Model *model,
				     Component *comp);
  unsigned count_crossing_lines(Model *model);
  void move_to_layer(layer_t layer)
  {
    outline.move_to_layer(layer);
  }

  Point center() const { return outline.center(); }

  bool is_router_pin() const;
  void draw(Canvas *c);
    

  void crossover(Pin *other);
  
  bool can_transpose(const Point &dir,
		     const Point &board_dim)
  {
    return outline.can_transpose(dir,
				 board_dim);
  }

  void transpose(const Point &dir)
  {
    outline.transpose(dir);
  }
  
  
  double sum_connection_lengths();
  void revector(Pin *from_pin, Pin *to_pin)
  {
    for (unsigned ix = 0;ix < connections.size(); ix++)
      {
	auto p = connections[ix];
	if (p == from_pin)
	  {
	    connections[ix] = to_pin;
	  }
      }
  }

  Pin *shallow_clone(Component *c, clone_map_t &map);
  void relink(Pin *m, clone_map_t &map);

  
  void setDescription(const std::string &descr)
  {
    this->info->description = descr;
  }
  
  
  void add_connection(Pin *to_pin)
  {
    connections.push_back(to_pin);
  }
};

#endif 
