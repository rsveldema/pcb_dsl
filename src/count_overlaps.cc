#include "create_model.h"
#include <algorithm>
#include "utils.h"

unsigned Model::count_overlaps()
{
  unsigned c = 0;
  for (auto p1 : components)
    {
      if (p1->is_board)
	{
	  continue;
	}
      
      for (auto p2 : components)
	{
	  if (p2->is_board)
	    {
	      continue;
	    }
	  
	  if (p1 == p2)
	    {
	      continue;
	    }
	  
	  if (p1->dim.layer != p2->dim.layer)
	    {
	      // cannnot overlap...
	      continue;
	    }
	  
	  double      d = p1->outline.distance(p2->outline);
	  double radius = p1->outline.getRadius();
	  
	  if (d < radius)
	    {
	      /*
	      utils::print("overlap of ", p1->name,
			   " with ", p2->name,
			   "--- dist = ", d, " radius = ", radius);
	      */
	      c += 1;
	    }
	}
    }
  return c;
}

