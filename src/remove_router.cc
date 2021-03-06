#include "create_model.hpp"
#include "utils.hpp"

static
Component *next_router(Component *comp)
{
  if (comp->info->is_router)
    {
      assert(comp->info->is_router);
      assert(comp->pins.size() == 2);
      assert(comp->pins[1]->info->name == "out");
      assert(comp->pins[1]->size() > 0);
      
      if (comp->pins[1]->size() == 1)
	{	  
	  auto to_pin = comp->pins[1]->get(0);
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
      for (unsigned ci=0;ci<comp->pins.size();ci++)
	{
	  auto pin = comp->pins[ci];

	  for (unsigned i=0;i<pin->size();i++)
	    {
	      auto conn = pin->get(i);

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
  for (unsigned ci=0; ci < pins.size(); ci++)
    {
      auto p = pins[ci];

      const unsigned count = p->size();
      for (unsigned i = 0; i < count; i++)
	{
	  auto from_pin = p->get(i);
	  if (from_pin->component == from)
	    {
	      auto to_pin = to->find_pin_by_id(from_pin->info->id);
	      assert(to_pin);
	      p->set(i, to_pin);
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
  bool did_something = true;
  while (did_something)
    {
    retry:

      did_something = false;
      InMap in_map(this);
      for (auto A : components)
	{
	  if (auto B = next_router(A))
	    {
	      if (auto C = next_router(B))
		{
		  if (auto D = next_router(C))
		    {
		      if (in_map.num_incoming_edges(B->pins[0]) == 1 &&
			  in_map.num_incoming_edges(C->pins[0]) == 1)
			{
			  fprintf(stderr, "found router chain-2!\n");
			  
			  A->pins[1]->set_layer(B->pins[1]->get_layer());
			  D->pins[0]->set_layer(B->pins[1]->get_layer());
			  
			  A->move_pin_connection(B,
						 D);
			  
			  utils::erase(components, B);
			  utils::erase(components, C);
			  
			  this->mman.free(B);
			  this->mman.free(C);

			  did_something = true;
			  goto retry;
			}
		    }
		}
	    }
	}
    }
}
