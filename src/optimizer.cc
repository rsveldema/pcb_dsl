#include "create_model.h"
#include <algorithm>
#include "utils.h"

auto POPULATION_NUM_GROUPS =  1u;
auto POPULATION_GROUP_SIZE = 10u;

auto SELECTION_FILTER_SIZE   = unsigned(0.3 * POPULATION_GROUP_SIZE);
auto CROSSOVER_PROBABILITY   = unsigned(0.8 * POPULATION_GROUP_SIZE);
auto MUTATION_PROBABILITY    = unsigned(0.2 * POPULATION_GROUP_SIZE);
auto NUM_BENDS_PER_ROUTE     = 2u;

bool contains(clone_map_t &routers,
	      Component *p)
{
  return routers.find(p) != routers.end();
}


void revector_connections_to_router(clone_map_t &routers,
				    Component *router,
				    Model *model,
				    Pin *from_pin)
{
  //# see if there is another component that has a link to our pin:
  //#print("revector ")
  for (auto comp : model->components)
    {
      if (! contains(routers, comp)) //not comp in routers
	{
	  for (auto other_pin : comp->pins)
	    {
	      other_pin->revector(from_pin, router->pins[0]);
	    }
	}
    }
}


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

void Component::crossover(Component *other)
{
  auto k = outline;
  outline  = other->outline;
  other->outline = k;
  //outline.xparent = this;
  //other->outline.xparent = other;    
}

void Model::crossover(Model *other)
{
  auto size = components.size();
  auto ix = randrange(size);

  auto c1 = components[ix];
  auto c2 = other->components[ix];
  
  assert(c1->id == c2->id);
  assert(c1->name == c2->name);
  c1->crossover(c2);
}


void Component::place_routing_components(Model *model, const Point &dim)
{
  for (auto p : pins)
    {
      if (p->connections.size() == 0)
	{
	  continue;
	}
      
      clone_map_t routers;
      routers[this] = this;
      
      Component *last = NULL;
      for (unsigned k = 0; k < NUM_BENDS_PER_ROUTE; k++)
	{
	  auto router = model->create_router();
	  routers[router] = router;

	  if (! last) {
	    router->pins[1]->connections = p->connections;
	    p->connections = { router->pins[0] };
	  } else {
	    router->pins[1]->connections = last->pins[1]->connections;
	    last->pins[1]->connections = { router->pins[0] };
	  }
	  last = router;
	}
      revector_connections_to_router(routers, last, model, p);
    }
}

void Model::do_place_routing_components(const Point &dim)
{
  for (auto c : components)
    {
      if (! c->is_router)
	{
	  c->place_routing_components(this, dim);
	}
    }
}

Model* Model::place_routing_components(const Point &dim)
{
  auto m = deepclone();
  m->do_place_routing_components(dim);
  return m;
}


unsigned Model::count_overlaps()
{
  unsigned c = 0;
  for (auto p1 : components)
    {
      if (p1->is_board)
	continue;
      for (auto p2 : components)
	{
	  if (p2->is_board)
	    continue;
	  if (p1 == p2)
	    continue;

	  
	  double d = p1->outline.distance(p2->outline);
	  double radius = p1->outline.getRadius();
	  
	  if (d < radius)
	    {
	      utils::print("overlap of ", p1->name,
			   " with ", p2->name,
			   "--- ", d, " radius = ", radius);
	      c += 1;
	    }
	}
    }
  return c;
}

double Pin::sum_connection_lengths()
{
  double s = 0;
  auto center = outline.center();
  for (auto c : connections)
    {
      s += center.distance(c->outline.center());
    }
  return s;  
}

double Component::sum_connection_lengths()
{
  double s = 0;
  for (auto c : pins)
    {
      s += c->sum_connection_lengths();
    }
  return s;  
}


double Model::sum_connection_lengths()
{
  double s = 0;
  for (auto c : components)
    {
      s += c->sum_connection_lengths();
    }
  return s;
}

score_t Model::score()
{
  auto my_num_overlaps    = this->count_overlaps();
  auto my_len             = this->sum_connection_lengths();
  score_t s = (my_num_overlaps * 100) + (my_len * 2);
  return s;
}
		



class Generation
{
private:
  int group_id;
  std::vector<Model*> models;
  
public:
  Generation(int _group_id)
    : group_id(_group_id)
  {
  }

  void add(Model *m)
  {
    models.push_back(m);
  }

  bool should_mutate() const
  {
    return randrange(POPULATION_GROUP_SIZE) < MUTATION_PROBABILITY;
  }

  bool should_crossover() const
  {
    return randrange(POPULATION_GROUP_SIZE) < CROSSOVER_PROBABILITY;
  }

  void change(unsigned iteration)
  {
    for (unsigned i=0;i<models.size();i++)
      {
	Model *model = models[i];
	if (this->should_mutate())
	  {
	    model->random_move_components(Point(10, 10, 0)); //w.div(iteration), h.div(iteration))
	  }
	if (this->should_crossover())
	  {
	    unsigned k = randrange(0, models.size());
	    if (k != i)
	      {
		auto other = models[k];
		model->crossover(other);
	      }
	  }
      }
  }

  static int comparer(std::pair<score_t,Model*> &p1,
		      std::pair<score_t,Model*> &p2)
  {
    return p1.first - p2.first;
  }
		      
  
  void selection(unsigned iteration)
  {
    std::vector<std::pair<score_t,Model*>> scores;

    for (auto model : models)
      {
	int score = model->score();
	scores.push_back( { score, model } );
      }

    std::sort(scores.begin(), scores.end(), comparer);

    // TODO: delete bad ones.
    models.clear();
    for (unsigned i = 0; i < POPULATION_GROUP_SIZE; i++)
      {
	if (i < SELECTION_FILTER_SIZE)
	  {
	    models.push_back(scores[i].second);
	  }
	else
	  {
	    auto k = i % SELECTION_FILTER_SIZE;
	    auto cloned = scores[k].second->deepclone();
	    cloned->random_move_components(Point(5, 5, 0));
	    models.push_back(cloned);
	  }
	  
      }

    //scores[0].second->writeSVG(utils::str("group-best-", iteration, ".svg"));
  }
        
  void optimize(unsigned iteration)
  {
    this->change(iteration);
    this->selection(iteration);
  }
  
  Model* find_best()
  {
      Model* best = NULL;
      score_t best_score = 0;
      for (auto m : this->models)
	{
	  int score = m->score();
	  if (best == NULL)
	    {
	      best = m;
	      best_score = score;
	    }
	  else
	    {
	      if (score < best_score)
		{
		  best_score = score;
		  best = m;
		}
	    }
	}
      return best;
    }
};
    

class NestedGeneration
{
public:
  std::vector<Generation *> nest;
	  
  void optimize(unsigned iteration)
  {
    for (auto p : nest)
      {
	p->optimize(iteration);
      }
  }
  
    
  void add(Generation *p)
  {
    nest.push_back(p);
  }

  Model* find_best()
  {
    Model *best = NULL;
    score_t best_score = 0;
    
    for (auto k : this->nest)
      {
	auto b = k->find_best();
	score_t score = b->score();
	if (best == NULL)
	  {
	    best = b;
	    best_score = score;
	  }
	else
	  {
	    if (score < best_score)
	      {
		best_score = score;
		best = b;
	      }
	  }
      }
    return best;
  }
};


NestedGeneration* create_initial_generation(Model *model)
{
  model->writeSVG("initial.svg");
  
  auto dim = model->board_dim;
  auto start_model = model->deepclone();
  auto random_routed = start_model->place_routing_components(dim);
  random_routed->writeSVG("random_routed.svg");
    
  auto nested = new NestedGeneration();
  for (unsigned i = 0; i < POPULATION_NUM_GROUPS; i++)
    {
      auto inner = new Generation(i);
      nested->add(inner);

      for (unsigned j = 0; j < POPULATION_GROUP_SIZE; j++)
	{
	  auto clone = random_routed->deepclone();
	  clone->initial_random_move_components();
	  inner->add(clone);
	}
    }
  return nested;
}

Model* optimize_model(Model *model,
		      unsigned time_limit_secs)
{
  printf("creating initial population");
  auto nested = create_initial_generation(model);
  printf("DONE: starting optimization process");

  unsigned iteration = 1;
  auto now = currentTimeSecs();
  auto old = now;
  auto end = now + time_limit_secs;
  while (now < end)
    {
      nested->optimize(iteration);
      now = currentTimeSecs();
      
      if (int(now) != int(old))
	{
	  auto best = nested->find_best();
            
	  if (best)
	    {
	      best->writeSVG(utils::str("best-iteration-", iteration, ".svg"));
	    }
	  else
	    {
	      printf("no best found?");
	    }
	  
	  old = now;
	  utils::print("left: ", long(end - now), " secs, done ", iteration);
	}
      iteration += 1;
    }

  utils::print("performed ", iteration,  " # iterations");
  return nested->find_best();
}
