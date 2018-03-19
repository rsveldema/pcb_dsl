#include "create_model.h"
#include <algorithm>
#include "utils.h"

void Pin::crossover(Pin *other)
{
  auto k = outline;
  outline  = other->outline;
  other->outline = k;
}

void Component::crossover(Component *other)
{
  assert(get_layer() == other->get_layer());
  assert(other->info->name == info->name);

  for (unsigned i=0;i<pins.size();i++)
    {
      auto p1 = pins[i];
      auto p2 = other->pins[i];
      
      if (p1->get_layer() != p2->get_layer())
	{
	  return;
	}
    }
  
  
  auto k = outline;
  outline  = other->outline;
  other->outline = k;

  k = bounding_box;
  bounding_box = other->bounding_box;
  other->bounding_box = k;
  
  //outline.xparent = this;
  //other->outline.xparent = other;

  for (unsigned i=0;i<pins.size();i++)
    {
      auto p1 = pins[i];
      auto p2 = other->pins[i];
      
      assert(p1->get_layer() == p2->get_layer());
      p1->crossover(p2);
    }
}

void Model::crossover(Model *other)
{
  auto size = components.size();
  auto ix = randrange(size);
  auto c1 = components[ix];

  auto c2 = other->find_component_by_id(c1->id);
  if (c2 != NULL)
    {
      assert(c1->info == c2->info);
      c1->crossover(c2);
    }
}
