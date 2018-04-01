#include "create_model.hpp"
#include <algorithm>
#include "utils.hpp"

static constexpr bool VERBOSE = false;


void Pin::add_connection_lengths(length_score_t &s,
				 Model *m)
{
  auto center = outline.center();

  for (unsigned i=0;i<size(); i++)
    {
      Pin *other = connections[i];

      uint32_t max_dist = m->info->get_max_distance();
      if (this->overlaps(other))
	{
	  if (VERBOSE)
	    {
	      printf("overlapping pins %s and %s\n",
		     this->component->info->name.c_str(),
		     other->component->info->name.c_str());
	    }
	  s.add(score_elt_t(0,
			    max_dist,
			    "LEN",
			    Importance::SUM_LENGTHS));
	}      
      else
	{
	  uint32_t d = center.distance(other->outline.center());
	  s.add(score_elt_t(d,
			    max_dist,
			    "LEN",
			    Importance::SUM_LENGTHS));
	}
    }
}

void Component::add_connection_lengths(length_score_t &s,
				       Model *m)
{
  for (unsigned ci=0;ci<pins.size();ci++)
    {
      auto pin = pins[ci];
      pin->add_connection_lengths(s, m);
    }
}

void Model::add_connection_lengths(length_score_t &s)
{
  for (auto c : components)
    {
      c->add_connection_lengths(s, this);
    }
}
