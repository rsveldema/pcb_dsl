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
  auto k = outline;
  outline  = other->outline;
  other->outline = k;
  //outline.xparent = this;
  //other->outline.xparent = other;

  for (unsigned i=0;i<pins.size();i++)
    {
      auto p1 = pins[i];
      auto p2 = other->pins[i];

      if (p1->get_layer() == p2->get_layer())
	{
	  p1->crossover(p2);
	}
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
      assert(c1->id == c2->id);
      assert(c1->name == c2->name);
      c1->crossover(c2);
    }
}