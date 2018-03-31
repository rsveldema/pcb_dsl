#ifndef COMPONENT_H_H__H_
#define COMPONENT_H_H__H_

#include <map>
#include "my_vector.hpp"

#include "parser.hpp"

class Pin;


/** holds info shared by all instances of a given component type.
 */
class ComponentInfo
{
 public:
  MillimeterPoint dim; // width,height,layer
  Point *fixed_position = NULL;
  std::string name;
  bool is_ground = false;
  bool is_router = false;
  bool is_board = false;
  bool is_rotateable = false;
  std::string component_type;

  ComponentInfo(const std::string &_name, bool _is_router);
};

class Component
{
  static constexpr unsigned MAX_PINS_PER_COMPONENT = 64;
  
 public:
  ComponentInfo *info;  
  fixedsize_vector<Pin *, MAX_PINS_PER_COMPONENT> pins;
  Outline outline;
  Outline bounding_box;
  Model *model;
  unsigned id;
  
  Component() {}
  
  Component(ComponentInfo *_info, Model *m)
    : info(_info),
      model(m),
      id(get_unique_id())
  {
  }
  
 Component(const Component &c) = delete;
  
  Component(ComponentInfo *_info, Model *m, unsigned _id,
	    const Outline &_outline, const Outline &_bounding_box)
   : info(_info),
     outline(_outline),
     bounding_box(_bounding_box),
     model(m),
     id(_id)
  {
  }


 bool get_connection_angle_info(InMap &in_map,
				std::pair<double,double> &result);
  void add_bounding_box();
  void rotate(double radians);
  void random_rotate();

  void set_layer(layer_t l)
  {
    outline.set_layer(l);
    bounding_box.set_layer(l);

    for (unsigned i=0;i<pins.size();i++)
      {
	auto p = pins[i];
	p->set_layer(l);
      }
  }
  layer_t get_layer() const
  {
    assert(bounding_box.get_layer() == outline.get_layer());
    return outline.get_layer();
  }

  // if its a pin-table, add the pins to this component
  void add_table(Model *m, Table *table);
  
  void move_pin_connection(Component *from,
			   Component *to);

  std::string str() const
    {
      std::string ret = info->name;
      ret += "{";
      const char *sep = "";

      for (unsigned i=0;i<pins.size();i++)
      {
	auto p = pins[i];
	ret += sep;
	ret += p->str();
	sep = ", ";
      }
      ret += "}";
      return ret;
    }

  bool overlaps(const Component &c) const
  {
    return bounding_box.overlaps(c.bounding_box);
  }

  void crossover(Component *other);
  double sum_connection_lengths();

  Pin *find_pin_by_id(unsigned id) const;
  Pin *find_pin_by_name(const std::string &name);
  
  Component *shallow_clone(Model *m, clone_map_t &map);
  void relink(Model *m, clone_map_t &map);

  void create_outline();
  void draw(Canvas *c);

  void check();
  
  int resolve_length(const std::string &name)
  {
    if (name == "pins")
      return pins.size();
    abort();
  }

  bool can_transpose(const Point &dir,
		     const Point &board_dim)
  {
    return bounding_box.can_transpose(dir, board_dim);
  }  

  void transpose(const Point &dir)
  {
    outline.transpose(dir);
    bounding_box.transpose(dir);
    
    const unsigned count = pins.size();
    for (unsigned i=0;i<count;i++)
      {
	auto p = pins[i];
	p->transpose(dir);
      }
  }

  void gather_layer_map(LayerMap &map);
  void collect_crossing_pins(const Connection &connection,
			     std::vector<Pin*> &crossed);
  bool have_crossing_connection(const Connection &connection,
				Connection *crossed);
  bool add_layers_for_crossing_lines(Model *model,
				     MutationAdmin &admin);
  unsigned count_crossing_pins(Model *model);
  unsigned count_crossing_lines(Model *model);

  Pin *add_pin(Model *m, PinInfo *info);  
  
  Pin *get_pin_by_name(const std::string &s);
    
  Pin *get_pin_by_suffixes(const std::vector<dslParser::Access_suffixContext*> &suffix,
			   ModelContext &context, bool odd);

  Point center() { return bounding_box.center(); }
};


#endif
