#include "create_model.h"
#include "utils.h"

static
Component *next_router(Component *comp)
{
  if (comp->is_router)
    {
      assert(comp->is_router);
      assert(comp->pins.size() == 2);
      assert(comp->pins[1].info->name == "out");
      assert(comp->pins[1].connections.size() > 0);
      
      if (comp->pins.connections.size() == 1)
	{	  
	  auto to_pin = comp->pins[0].connections[0];
	  auto to_comp = to_pin->component;
	  if (to_comp->is_router)
	    {
	      return to_comp;
	    }
	}
    }
  return NULL;
}

class InMap
{
private:
  std::map<Pin*, unsigned> map;


  void add_in(Pin *p)
  {
    if (map.find(p) == map.end())
      {
	map[p] = 1;
      }
    else
      {
	map[p]++;
      }
  }

public:
  InMap in_map(Model *m)
  {
    for (auto comp : components)
      {
	for (auto pin : comp->pins)
	  {
	    for (auto conn : pin->connections)
	      {
		add_in(conn);
	      }
	  }
      }
  }
  
  unsigned num_incoming_edges(Pin *pin)
  {
    // if not in map, pin was unused.
    if (map.find(pin) == map.end())
      {
	return 0;
      }
    return map[pin];
  }
};

/** given router sequence:
 *       A -> B -> C -> D
 * we can remove B->C, iff:
 *     1) A and D are on the same plane
 *     2) no other references to B,C exist.
 */
void Model::remove_router_chain()
{
  InMap in_map(model);
  
  for (auto A : components)
    {
      if (auto B = next_router(model, A))
	{
	  if (auto C = next_router(model, B))
	    {
	      if (auto D = next_router(model, C))
		{
		  fprintf(stderr, "found router chain!\n");
		  if (in_map.num_incoming_edges(B->pins[0]) == 1 &&
		      in_map.num_incoming_edges(C->pins[0]) == 1)
		    {
		      model->remove(B);
		      model->remove(C);
		      return;
		    }
		}
	    }
	}
    }
}
