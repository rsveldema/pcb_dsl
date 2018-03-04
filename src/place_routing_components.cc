#include "create_model.h"
#include <algorithm>
#include "utils.h"

auto NUM_BENDS_PER_ROUTE     = 2u;


bool contains(clone_map_t &routers,
	      Component *p)
{
  return routers.find(p) != routers.end();
}


void revector_connections_to_router(clone_map_t &routers,
				    Component *router,
				    Model *model,
				    Pin *from_pin)
{
  //# see if there is another component that has a link to our pin:
  //#print("revector ")
  for (auto comp : model->components)
    {
      if (! contains(routers, comp)) //not comp in routers
	{
	  for (auto other_pin : comp->pins)
	    {
	      other_pin->revector(from_pin, router->pins[0]);
	    }
	}
    }
}


void Component::place_routing_components(Model *model, const Point &dim)
{
  for (auto p : pins)
    {
      if (p->connections.size() == 0)
	{
	  continue;
	}
      
      clone_map_t routers;
      routers[this] = this;
      
      Component *last = NULL;
      for (unsigned k = 0; k < NUM_BENDS_PER_ROUTE; k++)
	{
	  auto router = model->create_router();
	  routers[router] = router;

	  if (! last)
	    {
	      router->pins[1]->connections = p->connections;
	      p->connections = { router->pins[0] };
	    }
	  else
	    {
	      router->pins[1]->connections = last->pins[1]->connections;
	      last->pins[1]->connections = { router->pins[0] };
	    }
	  last = router;
	}
     revector_connections_to_router(routers, last, model, p);
    }
}

void Model::do_place_routing_components(const Point &dim)
{
  for (auto c : components)
    {
      if (! c->is_router)
	{
	  c->place_routing_components(this, dim);
	}
    }
}

Model* Model::place_routing_components(const Point &dim)
{
  auto m = deepclone();
  m->do_place_routing_components(dim);
  return m;
}
