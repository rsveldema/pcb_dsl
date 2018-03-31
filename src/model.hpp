#ifndef MODEL_H____H_
#define MODEL_H____H_

#include <string>
#include <vector>
#include <map>

#include "datasheet.hpp"
#include "utils.hpp"
#include "in_map.hpp"

struct score_t;
class Model;
class ModelContext;
class Component;
typedef std::map<Component*, Component*> clone_map_t;

#include "phys.hpp"
#include "pin.hpp"
#include "component.hpp"
#include "score.hpp"
#include "constraints.hpp"


class ModelInfo
{
 public:
  Point board_dim;
  std::map<std::string, int> constants;
  std::vector<Constraint *> constraints;
};


class MemoryManager
{
 private:
  static constexpr unsigned MAX_COMPONENTS = 128;
  static constexpr unsigned MAX_PINS = 4 * MAX_COMPONENTS;

  unsigned num_pins = 0;
  Pin pins[MAX_PINS];

  unsigned num_comp = 0;
  Component comp[MAX_COMPONENTS];

 public:
  MemoryManager()
    {
    }

  Pin *alloc_pin()
  {
    assert(num_pins < MAX_PINS);
    return &pins[num_pins++];
  }
  
  Component *alloc_comp()
  {
    assert(num_comp < MAX_COMPONENTS);
    return &comp[num_comp++];
  }
  
  void free(Pin *p)
  {
  }
  
  void free(Component *c)
  {
    for (auto p : c->pins)
      {
	free(p);
      }
  }
};

class Model
{
 public:
  MemoryManager mman;
  
  static constexpr unsigned MAGIC = 0xdeadbeed;
  
  std::vector<Component *> components;
  ModelInfo *info;
  unsigned live = MAGIC;
  
 public:
  Model(ModelInfo *_info)
    : info(_info)
    {
    }

  Model(const Model &c) = delete;
  Model &operator = (Model &m) = delete;
  
 public:
  unsigned get_num_sharp_angles();
  bool have_crossing_connection(const Connection &connection,
				Connection *crossed);
  void collect_crossing_pins(const Connection &connection,
			     std::vector<Pin*> &crossed);
  unsigned count_crossing_lines();
  unsigned count_crossing_pins();
  
  void add_layers_for_crossing_lines();
  double sum_connection_lengths();
  unsigned count_overlaps();  
  Component *create_router(const Point &pos);
  Model *clone();
  void writeSVG(const std::string &filename);
  void draw(Canvas *c);
  void random_move_components(const Point &range);
  void initial_random_move_components();
  void move_components_close_to_already_placed_components();
  void crossover(Model *m);
  void random_rotate_component();
  void compute_score(score_t &s);
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
  
  void check();

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