#ifndef MODEL_H____H_
#define MODEL_H____H_

#include <string>
#include <vector>
#include <map>

#include "datasheet.h"

unsigned get_unique_id();

class Model;
class ModelContext;

class Point
{
 public:
  float x, y;
  unsigned layer;

 public:
  Point(float _x, float _y, unsigned _layer)
    : x(_x), y(_y), layer(_layer)
    {
    }
  
  Point add(const Point &p) const
  {
    return Point(x + p.x, y + p.y, layer);
  }
  
  Point div(float d) const
  {
    return Point(x / d, y / d, layer);
  }

  Point mul(float d) const
  {
    return Point(x * d, y * d, layer);
  }
  
  bool can_transpose(const Point &dir, const Point &max) const
  {
    Point k = add(dir);
    if (k.x < 0) return false;
    if (k.y < 0) return false;
    if (k.x > max.x) return false;
    if (k.y > max.y) return false;
    return true;
  }
};

class Outline
{
 public:
  std::vector<Point> points;


  void addRect(const Point &ul,
	       const Point &lr)
  {
    points.push_back(ul);
    points.push_back(Point(lr.x, ul.y, ul.layer));
    points.push_back(lr);
    points.push_back(Point(ul.x, lr.y, ul.layer));
  }
  
  void transpose(const Point &dir)
  {
    for (int i=0;i<points.size(); i++)
      {
	points[i] = points[i].add(dir);
      }
  }
  
  Point center() const
  {
    Point c(0,0,0);
    bool first = true;
    for (auto p : points)
      {
	if (first)
	  {
	    c = p;
	  }
	else
	  {
	    p = c.add(p);
	  }
      }
    return c.div(points.size());
  }  
};

class Pin
{
 public:
  unsigned id;
  std::string name, mode;
  Outline outline;
  std::vector<Pin *> connections;

  Pin(const std::string &s)
    : id(get_unique_id()),
    name(s)
    {
    }

  void transpose(const Point &dir)
  {
    outline.transpose(dir);
  }
  
  void add_connection(Pin *to_pin)
  {
    connections.push_back(to_pin);
  }
};



class Component
{
 public:
  int width = 0;
  int height = 0;
  int layers = 0;
  
  bool has_data_sheet = false;
  int id;
  Point *fixed_position;
  std::string name;
  std::vector<Pin *> pins;
  Outline outline;
  Model *model;
  const bool is_router;
  const bool is_board;
  std::string component_type;
  std::vector<Table *> table_list;

 Component(Model *m, const std::string &_name, bool _is_router)
   : id(get_unique_id()),
    fixed_position(NULL),
    name(_name),    
    model(m),
    is_router(_is_router),
    is_board(_name == "board")
      {
      }

  int resolve_length(const std::string &name)
  {
    if (name == "pins")
      return pins.size();
    abort();
  }
  
  Table *find_table(const std::string &name)
  {
    for (auto t : table_list)
      {
	if (t->name == name)
	  {
	    return t;
	  }
      }
    return NULL;
  }

  void transpose(const Point &dir)
  {
    outline.transpose(dir);
    for (auto p : pins)
      {
	p->transpose(dir);
      }
  }

  Pin *add_pin(const std::string &s)
  {
    Pin *p = new Pin(s);
    pins.push_back(p);
    return p;
  }
  
  
  Pin *get_pin_by_name(const std::string &s)
  {
    for (auto p : pins) {
      if (p->name == s) {
	return p;	
      }
    }
    fprintf(stderr, "failed to find pin %s\n", s.c_str());
    abort();
  }
    
  Pin *get_pin_by_suffixes(const std::vector<dslParser::Access_suffixContext*> &suffix,
			   ModelContext &context, bool odd);
};

class Model
{
 public:
  Component *current_component = NULL;
  std::vector<Component *> components;
  std::map<std::string, int> constants;


  Component *find_component(const std::string &name)
  {
    for (auto c : components)
      {
	if (c->name == name)
	  {
	    return c;
	  }
      }
    
    abort();
    return NULL;
  }
};


#endif
