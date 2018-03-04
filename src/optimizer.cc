#include "create_model.h"
#include <algorithm>
#include "utils.h"

auto POPULATION_NUM_GROUPS =  1u;
auto POPULATION_GROUP_SIZE = 10u;

auto SELECTION_FILTER_SIZE   = unsigned(0.3 * POPULATION_GROUP_SIZE);
auto CROSSOVER_PROBABILITY   = unsigned(0.8 * POPULATION_GROUP_SIZE);
auto MUTATION_PROBABILITY    = unsigned(0.2 * POPULATION_GROUP_SIZE);



score_t Model::score()
{
  auto my_num_overlaps    = this->count_overlaps();
  auto my_len             = this->sum_connection_lengths();
  unsigned crossing_lines = this->count_crossing_lines();
  score_t s = (my_num_overlaps * 100) + (my_len * 2) + (crossing_lines * 1000);
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
	    //w.div(iteration), h.div(iteration))
	    model->random_move_components(Point(10, 10, 0));
	    model->add_layers_for_crossing_lines();
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

  static bool comparer(std::pair<score_t,Model*> &p1,
		       std::pair<score_t,Model*> &p2)
  {
    return p2.first > p1.first;
  }
		      
  
  void selection(unsigned iteration)
  {
    std::vector<std::pair<score_t,Model*>> scores;

    for (auto model : models)
      {
	score_t score = model->score();
	scores.push_back( { score, model } );
      }

    std::sort(scores.begin(), scores.end(), comparer);


    // TODO: delete bad ones.
    models.clear();
    for (unsigned i = 0; i < POPULATION_GROUP_SIZE; i++)
      {
	if (i < SELECTION_FILTER_SIZE)
	  {
	    //printf("score[%d]: %d\n", i, (int)scores[i].first);
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

	  //clone->writeSVG("random_routed2.svg");
	  
	  inner->add(clone);
	}
    }
  return nested;
}

Model* optimize_model(Model *model,
		      unsigned time_limit_secs)
{
  model->writeSVG("initial.svg");
      
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

  auto best = nested->find_best();
  utils::print("performed ", iteration,  " # iterations");
  return best;
}
