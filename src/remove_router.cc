#include "create_model.h"
#include "utils.h"

static
Component *next_router(Component *comp)
{
  if (comp->info->is_router)
    {
      assert(comp->info->is_router);
      assert(comp->pins.size() == 2);
      assert(comp->pins[1]->info->name == "out");
      assert(comp->pins[1]->connections.size() > 0);
      
      if (comp->pins[1]->connections.size() == 1)
	{	  
	  auto to_pin = comp->pins[1]->connections[0];
	  auto to_comp = to_pin->component;
	  if (to_comp->info->is_router)
	    {
	      return to_comp;
	    }
	}
    }
  return NULL;
}


InMap::InMap(Model *m)
{
  for (auto comp : m->components)
    {
      for (auto pin : comp->pins)
	{
	  for (auto conn : pin->connections)
	    {
	      add_in(pin, conn);
	    }
	}
    }
}


void Model::remove(Component *c,
		   InMap &in_map)
{
  // all references to this model should be removed.
  abort();
}

void Component::move_pin_connection(Component *from,
				    Component *to)
{
  for (auto p : pins)
    {
      const unsigned count = p->connections.size();
      for (unsigned i = 0; i < count; i++)
	{
	  auto from_pin = p->connections[i];
	  if (from_pin->component == from)
	    {
	      auto to_pin = to->find_pin_by_id(from_pin->info->id);
	      assert(to_pin);
	      p->connections[i] = to_pin;
	    }
	}      
    }
}

/** given router sequence:
 *       A -> B -> C -> D
 * we can remove B->C, iff:
 *     1) A and D are on the same plane
 *     2) no other references to B,C exist.
 */
void Model::remove_router_chain()
{
  InMap in_map(this);
  
  for (auto A : components)
    {
      if (auto B = next_router(A))
	{
	  if (auto C = next_router(B))
	    {
	      if (auto D = next_router(C))
		{
		  //fprintf(stderr, "found router chain!\n");
		  if (in_map.num_incoming_edges(B->pins[0]) == 1 &&
		      in_map.num_incoming_edges(C->pins[0]) == 1)
		    {
		      A->pins[1]->move_to_layer(B->pins[1]->get_layer());
		      D->pins[0]->move_to_layer(B->pins[1]->get_layer());
		      
		      A->move_pin_connection(B,
					     D);
		      
		      utils::erase(components, B);
		      utils::erase(components, C);
		      
		      delete B;
		      delete C;
		      return;
		    }
		}
	    }
	}
    }
}
