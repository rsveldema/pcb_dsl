#include <algorithm>
#include <thread>
#include <string.h>

#include "optimizer.hpp"
#include "create_model.hpp"
#include "utils.hpp"


#define USE_PARETO_FRONT          1
#define SUPPORT_MULTI_GEN_ELITE   1

constexpr auto POPULATION_NUM_GROUPS =  1u;
constexpr auto POPULATION_GROUP_SIZE = 32u;
constexpr auto NUM_KEPT_GROUP_BEST   =  4u; 
constexpr auto SELECTION_FILTER_SIZE   = unsigned(0.3 * POPULATION_GROUP_SIZE);

constexpr auto CROSSOVER_PROBABILITY_PERCENTAGE   = 60;
constexpr auto MUTATION_PROBABILITY_PERCENTAGE    = 5;
constexpr auto FIX_PROBABILITY_PERCENTAGE         = 20;
constexpr auto ROTATE_PROBABILITY_PERCENTAGE      = 3;

static
void print_config()
{
  fprintf(stderr, "================ CONFIG ====================\n");
#if USE_PARETO_FRONT
  fprintf(stderr, " ============> PARETO selector\n");
#else
  fprintf(stderr, " ============> LEX SORT selector\n");
#endif
  
#if SUPPORT_MULTI_GEN_ELITE
  fprintf(stderr, " ============> ELITE enabled\n");
#endif
  fprintf(stderr, "============================================\n");
}

static bool enable_gui;

std::string score_t::str() const
{
  const char *comma = "";
  std::string str("score<");
  for (unsigned prio = 0; prio < score_t::PRIO_LEVELS; prio++)
    {
      for (unsigned i=0;i<values[prio].size();i++)
	{
	  char buf[32];
	  if (values[prio].descr(i))
	    sprintf(buf, "%s:%d", values[prio].descr(i), values[prio].at(i));
	  else
	    sprintf(buf, "%d", values[prio].at(i));
	  
	  str += comma;
	  str += buf;
	  comma = ",";
	}
    }
      str += ">";
  return str;
}

bool score_t::is_better_than(const score_t &s, unsigned seed, unsigned prio) const
{
  if (int_comparer(s, seed, prio) < 0)
    {
      return true;
    }
  return false;
}

bool score_t::is_everywhere_better_than(const score_t &s, unsigned seed) const
{
  for (unsigned prio = 0; prio < score_t::PRIO_LEVELS; prio++)
    {
      if (int_comparer(s, seed, prio) > 0)
	{
	  return false;
	}
    }
  return true;
}


int score_t::int_comparer(const score_t &s, unsigned seed, unsigned prio) const
{
  assert(size(prio) == s.size(prio));

  const unsigned c = size(prio);
  unsigned ix = seed % c;
  for (unsigned i = 0; i < c; i++)
    {
      auto v1 =   values[prio].at(ix);
      auto v2 = s.values[prio].at(ix);
      if (v1 != v2)
	{
	  return v1 - v2;
	}
      ix++;
      if (ix == c)
	{
	  ix = 0;
	}
    }
  return 0;
}


/** called by qsort
 */
int qsort_int_comparer(const void *p1,
		       const void *p2)
{
  compare_t *a = (compare_t*)p1;
  compare_t *b = (compare_t*)p2;

  int v = 0;
  for (unsigned prio=0;prio < score_t::PRIO_LEVELS; prio++)
    {
      v = a->first.int_comparer(b->first, 0, prio);
      if (v < 0)
	{
	  break;
	}
    }
  return v;
}

#include "pareto.hpp"


/** 0 == perfect score, INF = forget it.
 */
void Model::compute_score(score_t &s)
{
  assert(live == MAGIC);
  
  auto overlaps = count_overlaps();
  auto conn_lengths = sum_connection_lengths();
  auto crossing_wires = count_crossing_lines();
  auto crossing_pins = count_crossing_pins();
  auto sharps = get_num_sharp_angles();
  //printf("overlaps == %d\n", (int) overlaps);

  s.add(0, overlaps, "OLAP");
  
  for (auto p : info->constraints)
    {
      p->score(this, s);
    }

  s.add(0, crossing_wires, "XW");
  s.add(0, crossing_pins, "XP");
  s.add(1, conn_lengths, "D");
  s.add(1, components.size(), "#C");
  s.add(1, num_layers(), "#L");
  s.add(1, sharps, "S");
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
	    static const Point min_range(MillimeterPoint(30, 30, 0));
	    Point range = model->info->board_dim.div(iteration);
	    range.inplace_max(10, 10);
	    assert(range.x > 0 && range.y > 0);	    
	    model->random_move_components(min_range.max(range));
	  }
	/*
	 if (should_fix())
	  {
	    model->add_layers_for_crossing_lines();
	  }
	 if (should_mutate())
	  {
	    model->remove_router_chain();
	  }
	 */
	if (should_rotate())
	  {
	    model->random_rotate_component();
	  }
	 if (should_crossover())
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
    score_t m_score;
    m->compute_score(m_score);
    if (best_models.size() < NUM_KEPT_GROUP_BEST)
      {
	best_models.push_back({ m_score, m->clone() });
	return;
      }
    for (unsigned i=0;i<NUM_KEPT_GROUP_BEST;i++)
      {
	if (m_score.is_everywhere_better_than(best_models[i].first, 0))
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

    //std::sort(scores.begin(), scores.end(), comparer);
    qsort(scores.data(), scores.size(), sizeof(std::pair<score_t, Model*>),
	  qsort_int_comparer);

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
	score_t score;
	model->compute_score(score);
	scores[i] = { score, model };
      }

    std::map<Model*, bool> selected;
#if USE_PARETO_FRONT
    use_pareto_front_selection(scores, selected);
#else
    use_plain_sort_selection(scores, selected);
#endif
    
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
	score_t score;
	m->compute_score(score);
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
	    if (score.is_everywhere_better_than(best_score, 0))
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
	    if (score.is_everywhere_better_than(best_score, 0))
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
		  //int overlaps = best->count_overlaps();
		  //printf(" have %d overlaps?\n", overlaps);
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
  print_config();
  
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
