#ifndef PIN_H__H_H__
#define PIN_H__H_H__

class Pin;


struct MutationAdmin
{
  static constexpr auto MAX_CROSSING_LINES_ELIMITED_PER_ROUND = 4;
  
  std::map<Pin*, bool> forbidden;

  bool limit_reached() const
  {
    return forbidden.size() >= MAX_CROSSING_LINES_ELIMITED_PER_ROUND;
  }
};

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

  unsigned id;
  std::string name;
  std::string description;

 public:
 PinInfo(const std::string &_name)
   : id(get_unique_id()),
    name(_name)
    {
    }
};

class Pin
{
 private:
  Outline outline;

 public:
  PinInfo *info;
  Component *component;
  std::vector<Pin *> connections;

 public:
 Pin(PinInfo *_info,
     Component *comp)
   : info(_info),
    component(comp)
    {
    }

   Pin(PinInfo *_info,
       Component *comp,
       const Outline &_outline)
     : outline(_outline),
    info(_info),
    component(comp)    
    {
    }

  Pin(const Pin &c) = delete;

 public:
  void set_outline(const Outline &outline)
  {
    this->outline = outline;
  }
  
  void minmax(min_max_t &d)
  {
    outline.minmax(d);
  }

  void addRect(const Point &s,
	       const Point &e)
  {
    outline.addRect(s, e);
  }
  
  void rotate(double radians,
	      const Point &center);
  
  std::string str() const
    {
      std::string ret = info->name;
      ret += "(";
      ret += outline.str();
      ret += ")";
      return ret;
    }

  bool overlaps(const Pin *p) const
  {
    return outline.overlaps(p->outline);
  }
  
  void check();
  
  layer_t get_layer() const { return outline.get_layer(); }
  void set_layer(layer_t l) { return outline.set_layer(l); }
  
  void gather_layer_map(LayerMap &map);
  bool have_crossing_connection(const Connection &connection,
				Connection *crossed);
  void route_around_conflict(Model *model,
			     Component *comp,
			     const Point &around);
  bool add_layers_for_crossing_lines(Model *model,
				     Component *comp,
				     MutationAdmin &admin);
  unsigned count_crossing_lines(Model *model);

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
