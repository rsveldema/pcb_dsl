#include "create_model.hpp"
#include <algorithm>
#include "utils.hpp"

static bool DUMP_INITIAL_PLACEMENTS = true;

class Cluster
{
private:
  Component *component;
  std::vector<Pin *> close_by;

public:
  Cluster(Component *c)
    : component(c)
  {
  }

  Component *comp() const
  {
    return component;
  }

  void add_close_by(Pin *c)
  {
    if (! comp()->info->is_router)
      {
	assert(c->get_layer() == component->get_layer());
      }
    close_by.push_back(c);
  }

  Point get_point_close_by() const
  {
    assert(close_by.size() > 0);

    Point dir;
    for (auto pin : close_by)
      {
	dir.add_inline(pin->center());
      }
    auto average = dir.div(close_by.size());

    auto range = MillimeterPoint(MillimeterLength(3),
				 MillimeterLength(3),
				 comp()->get_layer());
    auto ret = average.random_transpose(range);
    //printf("computed avg: %s, range %s, ret %s\n", average.str().c_str(), range.str().c_str(), ret.str().c_str());
    return ret;
  }
};

static
void place_them(Model *self,
		const std::vector<Cluster*> &placed)
{
  for (auto cluster : placed)
    {
      auto dir = cluster->get_point_close_by();
      //if (cluster.comp()->can_transpose(dir,
      //				self->info->board_dim))
      {
	cluster->comp()->transpose(dir);
      }
    }
}

static
bool is_placed(const std::vector<Cluster*> &placed,
	       Component *comp)
{
  for (auto c : placed)
    {
      if (c->comp() == comp)
	{
	  return true;
	}
    }
  return false;
}


static
Cluster* find_or_add_cluster(std::vector<Cluster*> &placed,
			     Component *comp)
{
  for (auto c : placed)
    {
      if (c->comp() == comp)
	{
	  return c;
	}
    }
  Cluster *c = new Cluster(comp);
  placed.push_back(c);
  return c;
}


static
void try_to_add_cluster(Component *comp,
			const std::vector<Cluster*> &already_placed,
			std::vector<Cluster*> &placed,
			InMap &map)
{
  for (auto pin : comp->pins)
    {
      assert(pin->component == comp);

      for (unsigned ix = 0; ix < pin->size(); ix++)
	{
	  auto conn_pin = pin->get(ix);
	  
	  if (is_placed(already_placed, conn_pin->component))
	    {
	      Cluster *cluster = find_or_add_cluster(placed, comp);
	      cluster->add_close_by(conn_pin);
	    }
	}

      if (map.num_incoming_edges(pin) > 0)
	{
	  for (auto conn_pin : map.get_in(pin))
	    {
	      if (is_placed(already_placed, conn_pin->component))
		{
		  Cluster *cluster = find_or_add_cluster(placed, comp);
		  cluster->add_close_by(conn_pin);
		}	  
	    }
	}
    }
}

static
void add_components_to_cluster(Model *self,
			       const std::vector<Cluster*> &already_placed,
			       std::vector<Cluster*> &placed,
			       InMap &map)
{
  for (auto comp : self->components)
    {
      if (! is_placed(already_placed, comp))
	{
	  try_to_add_cluster(comp, already_placed, placed, map);
	}
    }
}



void Model::move_components_close_to_already_placed_components()
{
  InMap map(this);
  std::vector<Cluster*> already_placed;
  for (auto c : components)
    {
      if (c->info->fixed_position)
	{
	  already_placed.push_back(new Cluster(c));
	}
    }

  while (already_placed.size() != components.size())
    {
      std::vector<Cluster*> components_to_cluster;
      add_components_to_cluster(this, already_placed, components_to_cluster, map);
      place_them(this, components_to_cluster);
      
      assert(components_to_cluster.size() > 0);
      for (auto c : components_to_cluster)
	{
	  already_placed.push_back(c);
	}
    }

  if (DUMP_INITIAL_PLACEMENTS)
    {
      static int counter;
      auto filename = utils::str("closeby-",counter++,".svg");
      system(utils::str("rm -f ", filename).c_str());
      writeSVG(filename);
    }
}
