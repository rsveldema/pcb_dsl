#include "create_model.h"
#include <algorithm>
#include "utils.h"


void Model::random_move_components(const Point &range)
{
  const Point board_dim = this->board_dim;
  const unsigned count = components.size();
  for (unsigned i=0;i<count;i++)
    {
      auto comp = components[i];
      if (! comp->info->fixed_position)
	{
	  auto dir = Point(randrange(-range.x, range.x),
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
  const Point board_dim = this->board_dim;
  for (auto comp : components)
    {
      if (! comp->info->fixed_position)
	{
	  auto dir = Point(randrange(board_dim.x),
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
