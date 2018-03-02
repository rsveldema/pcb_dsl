#ifndef MODEL_H____H_
#define MODEL_H____H_

#include <string>
#include <vector>
#include <map>

#include "datasheet.h"

std::string destringify(const std::string &s);
unsigned get_unique_id();
std::string normalize(const std::string &s);
bool valid_pin_name(const std::string &s);

class Model;
class ModelContext;

#include "phys.h"

class Pin
{
 public:
  unsigned id;
  std::string name, mode, description;
  Outline outline;
  std::vector<Pin *> connections;

  Pin(const std::string &s)
    : id(get_unique_id()),
    name(s)
    {
    }
  
  void setDescription(const std::string &descr)
  {
    this->description = descr;
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
  Page *package = NULL;

 Component(Model *m, const std::string &_name, bool _is_router)
   : id(get_unique_id()),
    fixed_position(NULL),
    name(_name),    
    model(m),
    is_router(_is_router),
    is_board(_name == "board")
      {
      }
  
  void create_outline()
  {
    auto p = findKnownPackage(component_type);
    p->create_outline(this);
  }
  
  void add_table(Table *table) {
    table_list.push_back(table);
    if (table->name == "pins")
      {
	for (auto row : table->rows)
	  {
	    auto name = normalize(row->get(0)->string);
	    if (valid_pin_name(name))
	      {
		auto pin = add_pin(name);
		pin->setDescription(row->get(1)->string);
	      }
	  }
      }
  }

  void add_package(Page *p)
  {
    package = p;
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
