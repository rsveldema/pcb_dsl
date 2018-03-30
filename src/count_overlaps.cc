#include "create_model.hpp"
#include <algorithm>
#include "utils.hpp"

unsigned Model::count_overlaps()
{
  unsigned c = 0;
  for (auto p1 : components)
    {
      if (p1->info->is_board)
	{
	  continue;
	}
      
      for (auto p2 : components)
	{
	  if (p2->info->is_board)
	    {
	      continue;
	    }
	  
	  if (p1 == p2)
	    {
	      continue;
	    }
	  
	  if (p1->overlaps(*p2))
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

