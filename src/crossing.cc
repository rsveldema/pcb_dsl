#include "create_model.h"
#include <algorithm>
#include "utils.h"

bool Connection::crosses(const Connection &connection)
{
  return Point::intersection(p1, p2,
			     connection.p1, connection.p2,
			     &conflict);
}

bool Pin::have_crossing_connection(const Connection &connection,
				   Connection *crossed)
{
  if (connection.p1.layer != get_layer())
    {
      return false;
    }
  auto p1 = outline.center();

  const unsigned count = connections.size();
  for (unsigned i=0;i<count;i++)
    {
      auto other_pin = this->connections[i];
 
      auto p2 = other_pin->outline.center();
      Point dummy;
      Connection other_connection {this, other_pin, p1, p2, dummy };

      if ((connection.to->component == other_connection.from->component) ||
	  (connection.p1 == other_connection.p2) ||
	  (connection.p2 == other_connection.p1))
	{
	  continue;
	}

      if (other_connection.crosses(connection))
	{
	  //printf("crossed connection found\n");
	  //bool test = (connection.p1 == other_connection.p2);
	  if (crossed)
	    {
	      *crossed = other_connection;
	    }
	  return true;
	}      
    }
  return false;
}

bool Component::have_crossing_connection(const Connection &connection,
					 Connection *crossed)
{
  if (info->is_board)
    {
      return false;
    }

  if (this == connection.from->component)
    {
      return false;
    }

  const unsigned count = pins.size();
  for (unsigned i=0;i<count;i++)
    {
      auto c = pins[i];
      if (c->have_crossing_connection(connection,
				      crossed))
	{
	  return true;
	}
    }
  return false;
}

bool Model::have_crossing_connection(const Connection &connection,
				     Connection *crossed)
{
  for (auto c : components)
    {
      if (c->have_crossing_connection(connection,
				      crossed))
	{
	  return true;
	}
    }
  return false;
}

bool Pin::add_layers_for_crossing_lines(Model *model,
					Component *comp,
					MutationAdmin &admin)
{
  auto center1 = outline.center();

  for (auto other_pin : connections)
    {
      if (admin.forbidden.find(other_pin) != admin.forbidden.end())
	{
	  continue;
	}

      // TODO: route around crossong compoments.
      
      auto center2 = other_pin->outline.center();
      Point dummy;
      Connection connection {this, other_pin, center1, center2, dummy };
      Connection crossed = connection;
      if (model->have_crossing_connection(connection,
					  &crossed))
	{
	  admin.forbidden[other_pin] = true;
	  
	  //utils::print("conflict occurred at ", crossed.conflict.str(), " between ", comp->name);
	  route_around_conflict(model,
				comp,
				crossed.conflict);
	  return true;
	}
    }
  return false;
}

unsigned Pin::count_crossing_lines(Model *model)
{
  unsigned count = 0;
  auto p1 = outline.center();

  const unsigned conn_count = connections.size();
  for (unsigned i=0;i<conn_count;i++)
    {
      auto other_pin = connections[i];

      auto p2 = other_pin->outline.center();
      Point dummy;
      Connection connection =  {this, other_pin, p1, p2, dummy};
      
      if (model->have_crossing_connection(connection,
					  NULL))
	{
	  count++;
	}
    }
  return count;
}

bool Component::add_layers_for_crossing_lines(Model *model,
					      MutationAdmin &admin)
{
  const unsigned count = pins.size();
  for (unsigned i=0;i<count;i++)
    {
      auto p = pins[i];
      if (p->add_layers_for_crossing_lines(model,
					   this,
					   admin))
	{
	  admin.forbidden[p] = true;
	  if (admin.limit_reached())
	    {
	      return true;
	    }
	}
    }
  return false;
}

unsigned Component::count_crossing_lines(Model *model)
{
  unsigned c = 0;
  const unsigned count = pins.size();
  for (unsigned i=0;i<count;i++)
    {
      auto p = pins[i];
      c += p->count_crossing_lines(model);
    }
  return c;
}

unsigned Model::count_crossing_lines()
{
  unsigned c = 0;
  const unsigned count = components.size();
  for (unsigned i=0;i<count;i++)
    {
      auto comp = components[i];
      c += comp->count_crossing_lines(this);
    }
  return c;
}

		
void Model::add_layers_for_crossing_lines()
{
  MutationAdmin admin;
  const unsigned count = components.size();
  for (unsigned i=0;i<count;i++)
    {
      auto c = components[i];
      if (c->add_layers_for_crossing_lines(this,
					   admin))
	{
	  if (admin.limit_reached())
	    {
	      break;
	    }
	}
    }
}

