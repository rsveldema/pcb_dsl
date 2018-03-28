#include <algorithm>
#include <thread>
#include <string.h>

#include "optimizer.h"
#include "create_model.h"
#include "utils.h"


enum class SelectionHeuristic
{
  PARETO_FRONT,
  PLAIN_SORT
};

//static SelectionHeuristic selection_heuristic = SelectionHeuristic::PARETO_FRONT;
static SelectionHeuristic selection_heuristic = SelectionHeuristic::PLAIN_SORT;

#define SUPPORT_MULTI_GEN_ELITE  1

constexpr auto POPULATION_NUM_GROUPS =  1u;
constexpr auto POPULATION_GROUP_SIZE = 32u;
constexpr auto NUM_KEPT_GROUP_BEST   =  4u; 
constexpr auto SELECTION_FILTER_SIZE   = unsigned(0.3 * POPULATION_GROUP_SIZE);

constexpr auto CROSSOVER_PROBABILITY_PERCENTAGE   = 20;
constexpr auto MUTATION_PROBABILITY_PERCENTAGE    = 4;
constexpr auto FIX_PROBABILITY_PERCENTAGE         = 8;
constexpr auto ROTATE_PROBABILITY_PERCENTAGE      = 4;

static bool enable_gui;

std::string score_t::str() const
{
  return utils::str("score<",
		    "#LAYER:", num_layers,
		    "#COMP:", num_comp,
		    ", OVELAP:", num_overlaps,
		    ", LEN:", connection_lengths,
		    ", CROSS:", crossing_lines,
		    ", SHARP: ", sharp_angles,
		    ">");
}

bool score_t::operator < (const score_t &s) const
{
  return int_comparer(s) < 0;
}


int score_t::int_comparer(const score_t &s) const
{
  assert(magic == MAGIC);
  assert(s.magic == MAGIC);
  if (num_overlaps != s.num_overlaps)             return num_overlaps - s.num_overlaps;
  if (crossing_lines     != s.crossing_lines)     return crossing_lines - s.crossing_lines;
  if (num_comp     != s.num_comp)                 return num_comp - s.num_comp;
  if (num_layers   != s.num_layers)               return num_layers - s.num_layers;
  if (connection_lengths != s.connection_lengths) return connection_lengths - s.connection_lengths;
  if (sharp_angles       != s.sharp_angles)       return sharp_angles - s.sharp_angles;
  return 0;
}

int int_comparer(const void *p1,
		 const void *p2)
{
  compare_t *a = (compare_t*)p1;
  compare_t *b = (compare_t*)p2;
  return a->first.int_comparer(b->first);
}

struct ParetoFront
{
  enum Criteria
    {
      COMP,
      LAYERS,
      LEN,
      NUM_CRITERIA
    };
  
  std::map<Criteria, std::pair<score_t, Model *> > scores;

  static constexpr double LEN_TOLERANCE = 10;
  static constexpr double COMP_TOLERANCE = 3;

  bool is_close(const score_t &newone,
		const score_t &seen)
  {
    if ((newone.connection_lengths - LEN_TOLERANCE) < seen.connection_lengths)
      {
	if ((newone.num_comp - COMP_TOLERANCE) < seen.num_comp)
	  {
	    return true;
	  }
      }
    return false;
  }
		
  
  bool acceptable(Criteria not_xc, const score_t &newone)
  {
    for (auto k : scores)
      {
	if (is_close(newone, k.second.first))
	  {
	    return true;
	  }
      }
    return false;
  }

  void tryAddToFront(const score_t &score, Model *model)
  {    
    std::pair<score_t, Model *> p = {score, model};
    if (scores.size() == 0)
      {
	scores[COMP]    = p;
	scores[LAYERS]  = p;
	scores[LEN]     = p;
	return;
      }
    if (scores[LAYERS].first.num_layers > score.num_layers &&
	acceptable(LAYERS, score))
      {
	scores[LAYERS] = p;
      }
    if (scores[COMP].first.num_comp > score.num_comp &&
	acceptable(COMP, score))
      {
	scores[COMP] = p;
      }
    if (scores[LEN].first.connection_lengths > score.connection_lengths &&
	acceptable(LEN, score))
      {
	scores[LEN] = p;
      }
  }

  void push_selected(std::map<Model*, bool> &selected)
  {
    for (auto it : scores)
      {
	selected[it.second.second] = true;
      }
  }
};


/** 0 == perfect score, INF = forget it.
 */
score_t Model::score()
{
  assert(live == MAGIC);
  
  auto overlaps = count_overlaps();
  auto conn_lengths = sum_connection_lengths();
  auto crosses = count_crossing_lines();
  auto sharps = get_num_sharp_angles();
  //printf("overlaps == %d\n", (int) overlaps);
  return {
    components.size(),
      num_layers(),
      overlaps,
      conn_lengths,
      crosses,
      sharps,
      score_t::MAGIC};
}


class Generation
{
private:  
  int group_id;
  std::vector<Model*> models;
#if SUPPORT_MULTI_GEN_ELITE
  std::vector<std::pair<score_t, Model*>> best_models;
#endif
  
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
    return randrange(100) < MUTATION_PROBABILITY_PERCENTAGE;
  }

  bool should_fix() const
  {
    return randrange(100) < FIX_PROBABILITY_PERCENTAGE;
  }

  bool should_rotate() const
  {
    return randrange(100) < ROTATE_PROBABILITY_PERCENTAGE;
  }

  bool should_crossover() const
  {
    return randrange(100) < CROSSOVER_PROBABILITY_PERCENTAGE;
  }

  void change(unsigned iteration)
  {
    for (unsigned i=0;i<models.size();i++)
      {
	Model *model = models[i];
	if (should_mutate())
	  {
	    static const Point min_range(MillimeterPoint(10, 10, 0));
	    Point range = model->info->board_dim.div(iteration);
	    range.inplace_max(1, 1);
	    assert(range.x > 0 && range.y > 0);	    
	    model->random_move_components(min_range.max(range));
	  }	
	else if (should_fix())
	  {
	    model->add_layers_for_crossing_lines();
	  }
	else if (should_mutate())
	  {
	    model->remove_router_chain();
	  }
	else if (should_rotate())
	  {
	    model->random_rotate_component();
	  }
	else if (should_crossover())
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
		      
  void delete_non_selected_models(std::map<Model*, bool> &selected)
  {
    const unsigned count = models.size();
    for (unsigned i=0;i<count;i++)
      {
	auto model = models[i];
	assert(model);
	if (selected.find(model) == selected.end())
	  {
	    delete model;
	    models[i] = NULL;
	  }
      }
    
    models.clear();
    assert(models.size() == 0);
  }

#if SUPPORT_MULTI_GEN_ELITE
  void try_to_add_to_best_models(Model *m)
  {
    score_t m_score = m->score();
    if (best_models.size() < NUM_KEPT_GROUP_BEST)
      {
	best_models.push_back({ m_score, m->clone() });
	return;
      }
    for (unsigned i=0;i<NUM_KEPT_GROUP_BEST;i++)
      {
	if (m_score < best_models[i].first)
	  {
	    delete best_models[i].second;
	    best_models[i] = { m_score, m->clone() };
	    return;
	  }
      }
  }
#endif

  void create_new_generation(std::map<Model*, bool> &selected)
  {
    delete_non_selected_models(selected);
    std::vector<Model*> array;
    for (auto k : selected)
      {
	array.push_back(k.first);
#if SUPPORT_MULTI_GEN_ELITE
	try_to_add_to_best_models(k.first);
#endif
      }    
    
    assert(array.size() == selected.size());
    assert(selected.size() <= POPULATION_GROUP_SIZE);
    
    for (unsigned i = 0; i < POPULATION_GROUP_SIZE; i++)
      {
	if (i < selected.size())
	  {
	    //printf("score[%d]: %d\n", i, (int)scores[i].first);
	    models.push_back(array[i]);
	  }
#if SUPPORT_MULTI_GEN_ELITE
	else if (i < (selected.size() + best_models.size()))
	  {
	    //printf("injection of best models\n");
	    models.push_back(best_models[i-selected.size()].second->clone());
	  }
#endif
	else
	  {	    
	    auto k = i % selected.size();
	    assert(k < selected.size());
	    
	    auto cloned = array[k]->clone();
	    static const Point range(MillimeterPoint(5, 5, 0));
	    cloned->random_move_components(range);
	    models.push_back(cloned);
	  }	  
      }
  }

  void use_plain_sort_selection(std::array<compare_t, POPULATION_GROUP_SIZE> &scores,
				std::map<Model*, bool> &selected)
  {
    assert(scores.size() == POPULATION_GROUP_SIZE);
    for (auto it : scores)
      {
	assert(it.first.magic == score_t::MAGIC);
      }
    //std::sort(scores.begin(), scores.end(), comparer);
    qsort(scores.data(), scores.size(), sizeof(std::pair<score_t, Model*>),
	  int_comparer);

    static_assert(SELECTION_FILTER_SIZE < POPULATION_GROUP_SIZE);
    for (unsigned i = 0; i < SELECTION_FILTER_SIZE; i++)
      {
	assert(i < scores.size());
	Model *model = scores[i].second;
	selected[model] = true;
      }
  }

  void use_pareto_front_selection(std::array<compare_t, POPULATION_GROUP_SIZE> &scores,
				  std::map<Model*, bool> &selected)
  {
    ParetoFront front;
    for (auto p : scores)
      {
	auto score  = p.first;
	auto model = p.second;
	assert(model);
	
	front.tryAddToFront(score, model);
      }
    front.push_selected(selected);
  }


  void selection(unsigned iteration)
  {
    std::array<compare_t, POPULATION_GROUP_SIZE> scores;
    memset(&scores, 0, sizeof(scores));

    assert(models.size() == POPULATION_GROUP_SIZE);
    for (unsigned i=0;i<models.size();i++)
      {
	auto model = models[i];
	score_t score = model->score();
	scores[i] = { score, model };
      }

    std::map<Model*, bool> selected;
    switch (selection_heuristic)
      {
      case SelectionHeuristic::PARETO_FRONT: use_pareto_front_selection(scores, selected); break;
      case SelectionHeuristic::PLAIN_SORT:   use_plain_sort_selection(scores, selected); break;
      default: abort();
      }

    assert(selected.size() > 0);
    create_new_generation(selected);
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
#if 1
    for (auto m : this->models)
      {
	score_t score = m->score();
#else
    for (auto mi : this->best_models)
      {
	Model *m = mi.second;
	score_t score = mi.first;//score();
#endif
	
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


static
NestedGeneration* create_initial_generation(Model *initial_model,
					    InitialPlacement placement)
{
  //auto dim = initial_model->info->board_dim;
  auto start_model = initial_model->clone();
  start_model->writeSVG("random_routed.svg");
    
  auto nested = new NestedGeneration();
  for (unsigned i = 0; i < POPULATION_NUM_GROUPS; i++)
    {
      auto inner = new Generation(i);
      nested->add(inner);

      for (unsigned j = 0; j < POPULATION_GROUP_SIZE; j++)
	{
	  auto clone = start_model->clone();
	  switch (placement)
	    {
	    case InitialPlacement::CLOSE_TO_ALREADY_PLACED:
	      clone->move_components_close_to_already_placed_components();
	      break;
	    case InitialPlacement::RANDOM:
	      clone->initial_random_move_components();
	      break;
	    }
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
		  //auto tmp = best->score();
		}
	    }
	  else
	    {
	      printf("no best found?");
	    }
	  
	  old = now;
	  utils::print("left: ", long(end - now),
		       " secs, done ", iteration,
		       ", got: ", score.str());
	}
      iteration += 1;
    }
  nested->iterations += iteration;
  printf("thread finished: %d\n", iteration);
}


Model* optimize_model(Model *model,
		      unsigned time_limit_secs,
		      bool enable_gui,
		      InitialPlacement initial_placement)
{
  ::enable_gui = enable_gui;
  Canvas *gui = NULL;

  auto nested = create_initial_generation(model,
					  initial_placement);  
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
