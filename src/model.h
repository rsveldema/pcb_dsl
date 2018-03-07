#ifndef MODEL_H____H_
#define MODEL_H____H_

#include <string>
#include <vector>
#include <map>

#include "datasheet.h"
#include "utils.h"
#include "in_map.h"

struct score_t;
class Model;
class ModelContext;
class Component;
typedef std::map<Component*, Component*> clone_map_t;

#include "phys.h"
#include "pin.h"
#include "component.h"



struct score_t
{
  size_t   num_comp = 0;
  size_t   num_layers = 0;
  unsigned num_overlaps = 0;
  double   connection_lengths = 0;
  unsigned crossing_lines = 0;

  void add_penalties();
  bool operator <(const score_t &s);

  std::string str() const;
};


class ModelInfo
{
 public:
  Point board_dim;
  std::map<std::string, int> constants;
};


class Model
{
 public:
  std::vector<Component *> components;
  ModelInfo *info;
  
 public:
  Model(ModelInfo *_info)
    : info(_info)
    {
    }

  ~Model()
    {
      const unsigned count = components.size();
      for (unsigned i=0;i<count;i++)
	{
	  delete components[i];
	}
    }
  
 public:
  bool have_crossing_connection(const Connection &connection,
				Connection *crossed);
  unsigned count_crossing_lines();
  void add_layers_for_crossing_lines();
  double sum_connection_lengths();
  unsigned count_overlaps();  
  Component *create_router(const Point &pos);
  Model *deepclone();
  void writeSVG(const std::string &filename);
  void draw(Canvas *c);
  void random_move_components(const Point &range);
  void initial_random_move_components();
  void crossover(Model *m);
  score_t score();
  void gather_layer_map(LayerMap &map);
  
  size_t num_layers()
  {
    LayerMap map;
    gather_layer_map(map);
    return map.size();
  }

  void remove_router_chain();
  void remove(Component *c,
	      InMap &in_map);
  
  void check()
  {
     for (auto c : components)
       {
	 c->check();
       }
  }

  void writeDOT(const std::string filename);

    std::string str() const
    {
      std::string ret = "model";
      ret += "{";
      const char *sep = "";
      for (auto p : components)
	{
	  ret += sep;
	  ret += p->str();
	  sep = ", ";
	}
      ret += "}";
      return ret;
    }

    
  Component *find_component(const std::string &name)
  {
    for (auto c : components)
      {
	if (c->info->name == name)
	  {
	    return c;
	  }
      }
    
    abort();
    return NULL;
  }

  Component *find_component_by_id(unsigned id)
  {
    for (auto c : components)
      {
	if (c->id == id)
	  {
	    return c;
	  }
      }
    return NULL;
  }
};


#endif
