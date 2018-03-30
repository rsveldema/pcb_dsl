#include "create_model.hpp"
#include <algorithm>
#include "utils.hpp"


void Model::random_move_components(const Point &range)
{
  const Point board_dim = this->info->board_dim;
  const unsigned count = components.size();
  for (unsigned i=0;i<count;i++)
    {
      auto comp = components[i];
      if (! comp->info->fixed_position)
	{
	  Dummy dummy;
	  auto dir = Point(dummy,
			   randrange(-range.x, range.x),
			   randrange(-range.y, range.y),
			   comp->info->dim.layer);
	  
	  //print("INITIAL_DIR TO PLACE: " + str(dir) + "  where comp [" + comp.name+ "] at " + str(comp.outline.center()))
	  if (comp->can_transpose(dir, board_dim))
	    {
	      comp->transpose(dir);
	    }
	  //#comp.rotate()
	}
    }
}
						      
void Model::initial_random_move_components()
{
  const Point board_dim = this->info->board_dim;
  for (auto comp : components)
    {
      if (! comp->info->fixed_position)
	{
	  Dummy dummy;
	  auto dir = Point(dummy,
			   randrange(board_dim.x),
			   randrange(board_dim.y),
			   comp->info->dim.layer);
	  
	  //print("INITIAL_DIR TO PLACE: " + str(dir) + "  where comp [" + comp.name+ "] at " + str(comp.outline.center()))
	  if (comp->can_transpose(dir, board_dim))
	    {
	      comp->transpose(dir);
	    }
	  //#comp.rotate()
	}
    }
}
