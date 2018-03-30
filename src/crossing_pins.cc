#include "create_model.hpp"
#include <algorithm>
#include "utils.hpp"

bool Pin::intersects_with(const Connection &o) const
{
  return outline.intersects_line(o.p1, o.p2);
}

void Component::collect_crossing_pins(const Connection &connection,
				      std::vector<Pin*> &crossed)
{
  if (info->is_board)
    {
      return;
    }

  const unsigned count = pins.size();
  for (unsigned i=0;i<count;i++)
    {
      auto c = pins[i];
      if (c != connection.from &&
	  c != connection.to)
	{
	  if (c->intersects_with(connection))
	    {
	      crossed.push_back(c);
	    }
	}
    }
}


void Model::collect_crossing_pins(const Connection &connection,
				  std::vector<Pin*> &crossed)
{
  for (auto c : components)
    {
      c->collect_crossing_pins(connection,
			       crossed);
    }
}


unsigned Pin::count_crossing_pins(Model *model)
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

      std::vector<Pin*> crossed;
      model->collect_crossing_pins(connection,
				   crossed);
      count += crossed.size();
    }
  return count;
}

unsigned Component::count_crossing_pins(Model *model)
{
  unsigned c = 0;
  const unsigned count = pins.size();
  for (unsigned i=0;i<count;i++)
    {
      auto p = pins[i];
      c += p->count_crossing_pins(model);
    }
  return c;
}

unsigned Model::count_crossing_pins()
{
  unsigned c = 0;
  const unsigned count = components.size();
  for (unsigned i=0;i<count;i++)
    {
      auto comp = components[i];
      c += comp->count_crossing_pins(this);
    }
  return c;
}


		
