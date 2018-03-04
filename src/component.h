#ifndef COMPONENT_H_H__H_
#define COMPONENT_H_H__H_

#include "parser.h"

/** holds info shared by all instances of a given component type.
 */
class ComponentInfo
{
 public:
  Point dim; // width,height,layer
  bool has_data_sheet = false;
  Point *fixed_position;
  std::string name;
  bool is_router;
  bool is_board;
  std::string component_type;
  std::vector<Table *> table_list;
  std::vector<Page *> pkg_list;

  ComponentInfo(const std::string &_name, bool _is_router);
};

class Component
{
 public:
  ComponentInfo *info;
  
  unsigned id;
  std::vector<Pin *> pins;
  Outline outline;
  Model *model;

 Component(ComponentInfo *_info, Model *m)
   : info(_info),
    id(get_unique_id()),
    model(m)
  {
  }

  std::string str() const
    {
      std::string ret = info->name;
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

  Pin *find_pin_by_id(unsigned id) const;
  
  Component *shallow_clone(Model *m, clone_map_t &map);
  void relink(Model *m, clone_map_t &map);

  void create_outline();
  void draw(Canvas *c);

  void check()
  {
    if (outline.size() == 0)
      {
	fprintf(stderr, "ERROR: component %s has no outline\n", info->name.c_str());
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
    info->pkg_list.push_back(p);
  }

  int resolve_length(const std::string &name)
  {
    if (name == "pins")
      return pins.size();
    abort();
  }
  
  Table *find_table(const std::string &name)
  {
    for (auto t : info->table_list)
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
    unsigned count = pins.size();
    for (unsigned i=0;i<count;i++)
      {
	auto p = pins[i];
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
    const unsigned count = pins.size();
    for (unsigned i=0;i<count;i++)
      {
	auto p = pins[i];
	p->transpose(dir);
      }
  }

  void gather_layer_map(LayerMap &map);
  bool have_crossing_connection(const Connection &connection,
				Connection *crossed);
  bool add_layers_for_crossing_lines(Model *model);
  unsigned count_crossing_lines(Model *model);

  Pin *add_pin(PinInfo *info)
  {
    Pin *p = new Pin(info, this);
    pins.push_back(p);
    return p;
  }
  
  
  Pin *get_pin_by_name(const std::string &s)
  {
    const unsigned count = pins.size();
    for (unsigned i=0;i<count;i++)
      {
	auto p = pins[i];
	
	if (p->info->name == s)
	  {
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
