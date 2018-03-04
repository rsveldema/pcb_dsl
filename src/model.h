#ifndef MODEL_H____H_
#define MODEL_H____H_

#include <string>
#include <vector>
#include <map>

#include "datasheet.h"
#include "utils.h"

class Model;
class ModelContext;
class Component;
typedef std::map<Component*, Component*> clone_map_t;

#include "phys.h"
#include "pin.h"
#include "component.h"

typedef double score_t;

class Model
{
 public:
  float WIRE_WIDTH = 0.1;
  
  Component *current_component = NULL;
  std::vector<Component *> components;
  std::map<std::string, int> constants;
  Point board_dim;

 public:
  bool have_crossing_connection(const Connection &connection);
  unsigned count_crossing_lines();
  void add_layers_for_crossing_lines();
  double sum_connection_lengths();
  unsigned count_overlaps();  
  Component *create_router();
  Model *deepclone();
  void writeSVG(const std::string &filename);
  void random_move_components(const Point &range);
  void initial_random_move_components();
  void crossover(Model *m);
  void do_place_routing_components(const Point &dim);
  Model* place_routing_components(const Point &dim);
  score_t score();


  Model()
    : board_dim(0, 0, 0)
    {
    }
    
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
