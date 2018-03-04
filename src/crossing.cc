#include "create_model.h"
#include <algorithm>
#include "utils.h"


bool Connection::crosses(const Connection &connection) const
{
  return Point::intersection(p1, p2,
			     connection.p1, connection.p2,
			     NULL);
}

bool Pin::have_crossing_connection(const Connection &connection)
{
  if (connection.p1.layer != outline.points[0].layer)
    {
      return false;
    }
  auto p1 = outline.center();
  
  for (auto other_pin : connections)
    {
      auto p2 = other_pin->outline.center();
      Connection other_connection {this, other_pin, p1, p2 };

      if (other_connection.from == connection.from &&
	  other_connection.to   == connection.to)
	{
	  continue;
	}	  

      if (other_connection.crosses(connection))
	{
	  return true;
	}      
    }
  return false;
}

bool Component::have_crossing_connection(const Connection &connection)
{
  if (is_board)
    {
      return false;
    }
  
  for (auto c : pins)
    {
      if (c->have_crossing_connection(connection))
	{
	  return true;
	}
    }
  return false;
}

bool Model::have_crossing_connection(const Connection &connection)
{
  for (auto c : components)
    {
      if (c->have_crossing_connection(connection))
	{
	  return true;
	}
    }
  return false;
}

void Pin::add_layers_for_crossing_lines(Model *model)
{
  auto p1 = outline.center();
  
  for (auto other_pin : connections)
    {
      auto p2 = other_pin->outline.center();
      Connection connection {this, other_pin, p1, p2 };
      
      if (model->have_crossing_connection(connection))
	{
	  layer_t layer = outline.points[0].layer + 1;
	  this->move_to_layer(layer);
	  other_pin->move_to_layer(layer);
	  return;
	}
    }
}

unsigned Pin::count_crossing_lines(Model *model)
{
  unsigned count = 0;
  auto p1 = outline.center();
  
  for (auto other_pin : connections)
    {
      auto p2 = other_pin->outline.center();
      Connection connection =  {this, other_pin, p1, p2 };
      
      if (model->have_crossing_connection(connection))
	{
	  count++;
	}
    }
  return count;
}

void Component::add_layers_for_crossing_lines(Model *model)
{
  for (auto p : pins)
    {
      p->add_layers_for_crossing_lines(model);
    }
}

unsigned Component::count_crossing_lines(Model *model)
{
  unsigned c = 0;
  for (auto p : pins)
    {
      c += p->count_crossing_lines(model);
    }
  return c;
}

unsigned Model::count_crossing_lines()
{
  unsigned c = 0;
  for (auto p : components)
    {
      c += p->count_crossing_lines(this);
    }
  return c;
}

		
void Model::add_layers_for_crossing_lines()
{
  for (auto c : components)
    {
      c->add_layers_for_crossing_lines(this);
    }
}

