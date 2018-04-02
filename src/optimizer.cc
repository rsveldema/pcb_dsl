#include <algorithm>
#include <thread>
#include <array>

#include <string.h>

#include "optimizer.hpp"
#include "create_model.hpp"
#include "utils.hpp"


#define SUPPORT_MULTI_GEN_ELITE   1

constexpr unsigned POPULATION_NUM_GROUPS =  1u;
constexpr unsigned POPULATION_GROUP_SIZE = 32u;
constexpr unsigned SELECTION_FILTER_SIZE   = unsigned(0.3 * POPULATION_GROUP_SIZE);

static_assert(SELECTION_FILTER_SIZE > 0);

#if SUPPORT_MULTI_GEN_ELITE   
constexpr unsigned NUM_KEPT_GROUP_BEST   =  (POPULATION_GROUP_SIZE / 2);
static_assert(NUM_KEPT_GROUP_BEST > 0);
#endif



constexpr unsigned CROSSOVER_PROBABILITY_PERCENTAGE   = 60;
constexpr unsigned MUTATION_PROBABILITY_PERCENTAGE    = 15;
constexpr unsigned FIX_PROBABILITY_PERCENTAGE         = 20;
constexpr unsigned ROTATE_PROBABILITY_PERCENTAGE      = 3;

static
void print_config()
{
  fprintf(stderr, "================ CONFIG ====================\n");
  fprintf(stderr, " ============> LEX SORT selector\n");
  
#if SUPPORT_MULTI_GEN_ELITE
  fprintf(stderr, " ============> ELITE enabled\n");
#endif
  fprintf(stderr, "============================================\n");
}

static bool enable_gui;

std::string score_t::str() const
{
  std::string str("score<");
  
  const char *comma = "";
  for (unsigned i=0;i<values.size();i++)
    {
      char buf[32];
      uint32_t n = values.at(i).raw();
      if (values.descr(i))
	{
	  sprintf(buf, "%s:%d", values.descr(i), n);
	}
      else
	sprintf(buf, "%d", n);
      
      str += comma;
      str += buf;
      comma = ",";
    }
  
  str += ">";
  return str;
}


bool score_t::is_better_than(score_t &s)
{
  if (int_comparer(s) >= 0)
    {
      return false;
    }
  return true;
}


/** negative values => this better than s
 */
int score_t::int_comparer(score_t &s) 
{
  assert(values.size() == s.values.size());
  
  values.sort();
  s.values.sort();
  
  const unsigned c = size();
  assert(c == s.size());
  int num_better = 0;
  int64_t num_better_score = 0;
  int num_worse = 0;
  for (unsigned i = 0; i < c; i++)
    {
      auto &k1 = values.at(i);
      auto &k2 = s.values.at(i);
      
      auto v1 = k1.normalized();
      auto v2 = k2.normalized();

      // shouldn't compare apples and oranges:
      assert(k1.get_importance() == k2.get_importance());
      assert(k1.descr() == k2.descr());

      if (v1 < v2)
	{
	  num_better++;
	  num_better_score += (v1 - v2);
	}
      else if (v1 > v2)
	{
	  num_worse++;
	}

      if ((i + 1) < c)
	{
	  auto next_v1 =   values.at(i + 1);
	  assert(next_v1.get_importance() >= k1.get_importance());

	  // same importance: keep going, otherwise, we should stop early
	  // to allow first the high-prio stuff to be optimized.
	  if (next_v1.get_importance() > k1.get_importance())
	    {
	      if (num_better > 0 &&
		  num_worse > 0)
		{
		  if (num_worse > num_better)
		    {
		      return num_worse - num_better;
		    }
		  else
		    {
		      return num_better_score;
		    }
		}
	    }
	}
    }
  
  if (num_worse > num_better)
    {
      return num_worse - num_better;
    }
  else
    {
      return num_better_score;
    }
}


/** called by qsort
 */
int qsort_int_comparer(const void *p1,
		       const void *p2)
{
  compare_t *a = (compare_t*)p1;
  compare_t *b = (compare_t*)p2;
  return a->first.int_comparer(b->first);
}


/** 0 == perfect score, INF = forget it.
 */
void Model::compute_score(score_t &s)
{
  assert(live == MAGIC);
  
  auto overlaps = count_overlaps();

  length_score_t ls;
  add_connection_lengths(ls);

  auto crossing_wires = count_crossing_lines();
  uint32_t max_crossing_wires = sqr(components.size());

  auto crossing_pins = count_crossing_pins();
  uint32_t max_crossing_pins = sqr(components.size() * 4);
  
  auto sharps = get_num_sharp_angles();
  //printf("overlaps == %d\n", (int) overlaps);
  
  s.add(score_elt_t(overlaps,
		    sqr(components.size()),
		    "OLAP",
		    Importance::OVERLAP));
  
  for (auto p : info->constraints)
    {
      p->score(this, s);
    }

  s.add(score_elt_t(num_layers(), 10, "#L", Importance::NUM_LAYERS));
  s.add(score_elt_t(crossing_pins,  max_crossing_pins, "XP", Importance::CROSSING_PINS));
  s.add(score_elt_t(crossing_wires, max_crossing_wires, "XW", Importance::CROSSING_WIRES));
  s.add(score_elt_t(sharps, components.size(), "S", Importance::SHARP_TURNS));
  s.add(ls);
  s.add(score_elt_t(components.size(), 1000, "#C", Importance::NUM_COMPONENTS));
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
	    static const Point min_range(MillimeterPoint(2, 2, 0));
#if USE_FAST_CHANGE_AT_START
	    Point range = model->info->board_dim.div(iteration);
	    range.inplace_max(10, 10);
	    assert(range.x > 0 && range.y > 0);
	    model->random_move_components(min_range.max(range));
#else
	    model->random_move_components(min_range);
#endif
	  }
	/*
	 else if (should_fix())
	  {
	    model->add_layers_for_crossing_lines();
	  }
	  else if (should_mutate())
	  {
	    model->remove_router_chain();
	  }
	*/
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
    score_t m_score;
    m->compute_score(m_score);
    if (best_models.size() < NUM_KEPT_GROUP_BEST)
      {
	best_models.push_back({ m_score, m->clone() });
	return;
      }
    for (unsigned i=0;i<NUM_KEPT_GROUP_BEST;i++)
      {
	if (m_score.is_better_than(best_models[i].first))
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

    /*
    fprintf(stderr,
	    "going to use %d selected, %d best and %d mutated selected\n",
	    selected.size(),
	    best_models.size(),
	    POPULATION_GROUP_SIZE - (selected.size() + best_models.size()));
    */
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
	    static const Point range(MillimeterPoint(1, 1, 0));
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
    use_plain_sort_selection(scores, selected);
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
	    if (score.is_better_than(best_score))
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
	    if (score.is_better_than(best_score))
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


Model* cpu_optimize_model(Model *model,
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
