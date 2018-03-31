#include "create_model.hpp"
#include <algorithm>
#include "utils.hpp"

static constexpr bool VERBOSE = false;

double Pin::sum_connection_lengths()
{
  double s = 0;
  auto center = outline.center();

  for (unsigned i=0;i<size(); i++)
    {
      Pin *other = connections[i];
    
      if (this->overlaps(other))
	{
	  if (VERBOSE)
	    {
	      printf("overlapping pins %s and %s\n",
		     this->component->info->name.c_str(),
		     other->component->info->name.c_str());
	    }
	  s += 0; // no distance to cover...
	}
      else
	{
	  s += center.distance(other->outline.center());
	}
    }
  return s;
}

double Component::sum_connection_lengths()
{
  double s = 0;

  for (unsigned ci=0;ci<pins.size();ci++)
    {
      auto pin = pins[ci];
      s += pin->sum_connection_lengths();
    }
  return s;  
}


double Model::sum_connection_lengths()
{
  double s = 0;
  for (auto c : components)
    {
      s += c->sum_connection_lengths();
    }
  return s;
}
