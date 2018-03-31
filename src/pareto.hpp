
#include "my_vector.hpp"

struct ParetoFront
{
  static constexpr unsigned MAX_PARETO_FRONT_SIZE = 16;
  
  bool init = false;
  fixedsize_vector<std::pair<score_t, Model *>, MAX_PARETO_FRONT_SIZE> scores;

  void tryAddToFront(const score_t &score, Model *model)
  {    
    std::pair<score_t, Model *> p = {score, model};
    if (! init)
      {
	init = true;
	for (unsigned i = 0; i < MAX_PARETO_FRONT_SIZE; i++)
	  {
	    scores.push_back(p);
	  }
	return;
      }

    for (unsigned prio = 0; prio < score_t::PRIO_LEVELS; prio++)
      {
	bool placed = false;
	  
	for (unsigned i = 0; i < score.size(prio); i++)
	  {
	    if (score.is_better_than(scores[i].first, i, prio))
	      {
		scores[i] = p;
		placed = true;
	      }
	  }

	if (placed)
	  {
	    // on high-prio already placed, no need to examine secondary characteristics.
	    break;
	  }
      }
  }

  void push_selected(std::map<Model*, bool> &selected)
  {
    for (unsigned i=0;i<scores.size();i++)
      {
	auto &it = scores[i];
	
	selected[it.second] = true;
      }
  }
};
