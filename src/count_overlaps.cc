#include "create_model.hpp"
#include <algorithm>
#include "utils.hpp"

unsigned Model::count_overlaps()
{
  unsigned c = 0;

  for (unsigned i = 0; i<components.size(); i++)
    {
      auto p1 = components[i];
      
      if (p1->info->is_board)
	{
	  continue;
	}

      for (unsigned j = i+1; j<components.size(); j++)
	{
	  auto p2 = components[j];
	  if (p2->info->is_board)
	    {
	      continue;
	    }

	  assert(p1 != p2);	  
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

