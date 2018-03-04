#ifndef COMPONENT_H_H__H_
#define COMPONENT_H_H__H_

#include "parser.h"

class Component
{
 public:
  Point dim; // width,height,layer  
  bool has_data_sheet = false;
  unsigned id;
  Point *fixed_position;
  std::string name;
  std::vector<Pin *> pins;
  Outline outline;
  Model *model;
  const bool is_router;
  const bool is_board;
  std::string component_type;
  std::vector<Table *> table_list;
  std::vector<Page *> pkg_list;

 Component(Model *m, const std::string &_name, bool _is_router)
   : dim(0, 0, 0),
    id(get_unique_id()),
    fixed_position(NULL),
    name(_name),    
    model(m),
    is_router(_is_router),
    is_board(_name == "board")
      {
      }


  std::string str() const
    {
      std::string ret = name;
      ret += "{";
      const char *sep = "";
      for (auto p : pins)
	{
	  ret += sep;
	  ret += p->str();
	  sep = ", ";
	}
      ret += "}";
      return ret;
    }

  void crossover(Component *other);
  double sum_connection_lengths();

  Pin *find_pin_by_id(unsigned id) const
  {
    for (auto p : pins)
      {
	if (p->id == id)
	  {
	    return p;
	  }
      }

    abort();
    return NULL;
  }
  
  Component *shallow_clone(Model *m, clone_map_t &map);
  void relink(Model *m, clone_map_t &map);
  
  void create_outline();
  void draw(Canvas *c);

  void check()
  {
    if (outline.size() == 0)
      {
	fprintf(stderr, "ERROR: component %s has no outline\n", name.c_str());
	abort();
      }
    
    for (auto c : pins)
      {
	c->check();
      }
  }
  
  void add_table(Table *table);
  void add_package(Page *p)
  {
    pkg_list.push_back(p);
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

  bool can_transpose(const Point &dir,
		     const Point &board_dim)
  {
    if (! outline.can_transpose(dir, board_dim))
      {
	return false;
      }
    for (auto p : pins)
      {
	if (! p->can_transpose(dir, board_dim))
	  {
	    return false;
	  }
      }
    return true;
  }  

  void transpose(const Point &dir)
  {
    outline.transpose(dir);
    for (auto p : pins)
      {
	p->transpose(dir);
      }
  }

  void gather_layer_map(LayerMap &map);
  bool have_crossing_connection(const Connection &connection,
				Connection *crossed);
  bool add_layers_for_crossing_lines(Model *model);
  unsigned count_crossing_lines(Model *model);

  Pin *add_pin(const std::string &s)
  {
    Pin *p = new Pin(this, s);
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


#endif
