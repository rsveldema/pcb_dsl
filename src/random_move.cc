#include "create_model.h"
#include <algorithm>
#include "utils.h"


void Model::random_move_components(const Point &range)
{
  const Point board_dim = this->board_dim;
  for (auto comp : components)
    {
      if (! comp->fixed_position)
	{
	  auto dir = Point(randrange(-range.x, range.x),
			   randrange(-range.y, range.y),
			   comp->dim.layer);
	  
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
      if (! comp->fixed_position)
	{
	  auto dir = Point(randrange(board_dim.x),
			   randrange(board_dim.y),
			   comp->dim.layer);
	  
	  //print("INITIAL_DIR TO PLACE: " + str(dir) + "  where comp [" + comp.name+ "] at " + str(comp.outline.center()))
	  if (comp->can_transpose(dir, board_dim))
	    {
	      comp->transpose(dir);
	    }
	  //#comp.rotate()
	}
    }
}
