#include "create_model.hpp"
#include <algorithm>
#include "utils.hpp"

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

static PinInfo *router_in = new PinInfo("in");
static PinInfo *router_out = new PinInfo("out");
static ComponentInfo *router_info = new ComponentInfo("router", true);

Component *Model::create_router(const Point &pos)
{
  //#print("creating router")
  auto storage = this->mman.alloc_comp();
  auto comp = new (storage) Component(router_info, this);
  components.push_back(comp);
  auto pin_in  = comp->add_pin(this, router_in);
  auto pin_out = comp->add_pin(this, router_out);
  
  auto s = Point();
  auto e = s.add(comp->info->dim);

  comp->outline.addRect(s, e);
  pin_in->addRect(s, e);
  pin_out->addRect(s, e);

  comp->transpose( pos );
  comp->add_bounding_box();
  return comp;
}


void Pin::route_around_conflict(Model *model,
				Component *comp,
				const Point &around)
{
  auto center = this->center();

  auto vec = around.sub(center);
  auto loc1 = center.add(vec.mul(0.9));
  auto loc2 = center.add(vec.mul(1.1));

  auto router1 = model->create_router(loc1);
  auto router2 = model->create_router(loc2);
  
  //clone_map_t routers;
  //routers[comp] = comp;
  // routers[router1] = router1;
  //routers[router2] = router2;

  //  before:  this -> P2
  //  after:   this -> R1 -> R2 -> P2

  layer_t new_layer = outline.get_layer() + 1;
    

  router1->pins[0]->set_layer(this->get_layer());
  router1->pins[1]->connections = { router2->pins[0] };
  router1->pins[1]->set_layer(new_layer);
  
  router2->pins[0]->set_layer(new_layer);  
  router2->pins[1]->connections = this->connections;
  router2->pins[1]->set_layer(this->get_layer());
  
  this->connections = { router1->pins[0] };

  //utils::print("done: ", model->str());
  model->writeDOT("routed.dot");
  //revector_connections_to_router(routers, router2, model, his);
}


