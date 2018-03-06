#include <algorithm>
#include <thread>

#include "create_model.h"
#include "utils.h"

constexpr auto POPULATION_NUM_GROUPS =  1u;
constexpr auto POPULATION_GROUP_SIZE = 10u;
constexpr double OVERLAP_PENALTY = 3.0;
constexpr auto SELECTION_FILTER_SIZE   = unsigned(0.3 * POPULATION_GROUP_SIZE);
constexpr auto CROSSOVER_PROBABILITY   = unsigned(0.8 * POPULATION_GROUP_SIZE);
constexpr auto MUTATION_PROBABILITY    = unsigned(0.2 * POPULATION_GROUP_SIZE);

static bool enable_gui;

std::string score_t::str() const
{
  return utils::str("score<",
		    "L:", num_layers,
		    ", O:", num_overlaps,
		    ", CL:", connection_lengths,
		    ", X:", crossing_lines,
		    ">");
}


bool score_t::operator <(const score_t &s)
{
  if (crossing_lines > s.crossing_lines) return false;
  if (num_layers > s.num_layers) return false;
  if (num_overlaps > s.num_overlaps) return false;
  if (connection_lengths > s.connection_lengths) return false;
  return true;
}


/** 0 == perfect score, INF = forget it.
 */
score_t Model::score()
{
  return { this->num_layers(),
      this->count_overlaps(),
      this->sum_connection_lengths(),
      this->count_crossing_lines()
      };
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
    return false;
    //return randrange(POPULATION_GROUP_SIZE) < CROSSOVER_PROBABILITY;
  }

  void change(unsigned iteration)
  {
    for (unsigned i=0;i<models.size();i++)
      {
	Model *model = models[i];
	if (this->should_mutate())
	  {
	    static const Point min_range(MillimeterPoint(10, 10, 0));
	    Point range = model->info->board_dim.div(iteration);
	    range.inplace_max(1, 1);
	    assert(range.x > 0 && range.y > 0);	    
	    model->random_move_components(min_range.max(range));	    
	  }
	
	model->add_layers_for_crossing_lines();
	model->remove_router_chain();
	
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
    return p1.first < p2.first;
  }
		      
  
  void selection(unsigned iteration)
  {
    std::vector<std::pair<score_t, Model*>> scores;

    assert(models.size() == POPULATION_GROUP_SIZE);    
    for (auto model : models)
      {
	score_t score = model->score();
	scores.push_back( { score, model } );
      }

    assert(scores.size() == POPULATION_GROUP_SIZE);    
    std::sort(scores.begin(), scores.end(), comparer);

    models.clear();
    assert(models.size() == 0);
    
    for (unsigned i = 0; i < POPULATION_GROUP_SIZE; i++)
      {
	Model *model = scores[i].second;
	
	if (i < SELECTION_FILTER_SIZE)
	  {
	    //printf("score[%d]: %d\n", i, (int)scores[i].first);
	    models.push_back(model);
	  }
	else
	  {
	    delete model;
	    scores[i].second = NULL;
	    
	    auto k = i % SELECTION_FILTER_SIZE;
	    assert(k < SELECTION_FILTER_SIZE);
	    
	    auto cloned = scores[k].second->deepclone();
	    static const Point range(MillimeterPoint(5, 5, 0));
	    cloned->random_move_components(range);
	    models.push_back(cloned);
	  }	  
      }
  }
        
  void optimize(unsigned iteration)
  {
    this->change(iteration);
    this->selection(iteration);
  }
  
  std::pair<score_t, Model*> find_best()
  {
    Model* best = NULL;
    score_t best_score;
    for (auto m : this->models)
      {
	score_t score = m->score();
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
    return {best_score, best};
  }
};
    

class NestedGeneration
{
public:
  std::atomic<unsigned> iterations;
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

  std::pair<score_t, Model*> find_best()
  {
    Model *best = NULL;
    score_t best_score;
    
    for (auto k : this->nest)
      {
	auto pair = k->find_best();
	Model *model = pair.second;
	score_t score = pair.first;
	if (best == NULL)
	  {
	    best = model;
	    best_score = score;
	  }
	else
	  {
	    if (score < best_score)
	      {
		best_score = score;
		best = model;
	      }
	  }
      }
    return {best_score, best};
  }
};


NestedGeneration* create_initial_generation(Model *initial_model)
{
  //auto dim = initial_model->info->board_dim;
  auto start_model = initial_model->deepclone();
  start_model->writeSVG("random_routed.svg");
    
  auto nested = new NestedGeneration();
  for (unsigned i = 0; i < POPULATION_NUM_GROUPS; i++)
    {
      auto inner = new Generation(i);
      nested->add(inner);

      for (unsigned j = 0; j < POPULATION_GROUP_SIZE; j++)
	{
	  auto clone = start_model->deepclone();
	  clone->initial_random_move_components();

	  //clone->writeSVG("random_routed2.svg");
	  
	  inner->add(clone);
	}
    }
  return nested;
}

static
void optimization_thread(NestedGeneration* nested,
			 unsigned time_limit_secs,
			 Canvas *gui)
{
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
	  auto pair = nested->find_best();
	  Model *best = pair.second;
	  score_t score = pair.first;
            
	  if (best)
	    {
	      if (enable_gui)
		{
		  gui->publish(best);
		}
	      else
		{
		  best->writeSVG(utils::str("best-iteration-", iteration, ".svg"));
		}
	    }
	  else
	    {
	      printf("no best found?");
	    }
	  
	  old = now;
	  utils::print("left: ", long(end - now), " secs, done ", iteration, ", got: ", score.str());
	}
      iteration += 1;
    }
  nested->iterations += iteration;
  printf("thread finished: %d\n", iteration);
}


Model* optimize_model(Model *model,
		      unsigned time_limit_secs,
		      bool enable_gui)
{
  ::enable_gui = enable_gui;
  Canvas *gui = NULL;
    
  auto nested = create_initial_generation(model);  
  if (enable_gui)
    {
      gui = Canvas::create_canvas();
      gui->publish(model);
    }
  else
    {
      model->writeSVG("initial.svg");
    }

  int num_worker_threads = 1;
  std::vector<std::thread *> threads;
  for (int i=0;i<num_worker_threads;i++)
    {
      auto t = new std::thread(optimization_thread,
			       nested,
			       time_limit_secs,
			       gui);
      threads.push_back(t);
    }

  if (enable_gui)
    {
      gui->run();
    }
  
  for (auto t : threads)
    {
      t->join();
    }

  
  auto pair = nested->find_best();
  Model *best_model = pair.second;
  //score_t best_score = pair.fist;
  utils::print("performed ", nested->iterations.load(), " # iterations");
  return best_model;
}
