#ifndef PIN_H__H_H__
#define PIN_H__H_H__

class Pin;

struct Connection
{
  Pin *from, *to;
  Point p1, p2;

  bool crosses(const Connection &connection) const;
};

class Pin
{
 public:
  unsigned id;
  std::string name, mode, description;
  Component *component;
  Outline outline;
  std::vector<Pin *> connections;

 public:
 Pin(Component *comp,
     const std::string &s)
   : id(get_unique_id()),
    name(s),
    component(comp)
    {
    }

  bool have_crossing_connection(const Connection &connection);
  void add_layers_for_crossing_lines(Model *model);
  unsigned count_crossing_lines(Model *model);
  void move_to_layer(layer_t layer)
  {
    outline.move_to_layer(layer);
  }
  
  void draw(Canvas *c)
  {
    outline.draw(c, name);
    for (auto connection : connections)
      {
	outline.drawLineTo(connection->outline.center(), c);
      }
  }

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
    this->description = descr;
  }
  
  void add_connection(Pin *to_pin)
  {
    connections.push_back(to_pin);
  }
};

#endif 
