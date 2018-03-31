
#include "my_vector.hpp"

struct ParetoFront
{
  static constexpr unsigned MAX_PARETO_FRONT_SIZE = score_data_t::MAX_SCORE_DATA;
  
  bool init = false;
  fixedsize_vector<std::pair<score_t, Model *>, MAX_PARETO_FRONT_SIZE> scores;

  void tryAddToFront(const score_t &score, Model *model)
  {
    assert(score.size() < MAX_PARETO_FRONT_SIZE);
    
    std::pair<score_t, Model *> p = {score, model};
    if (! init)
      {
	init = true;
	for (unsigned i = 0; i < score.size(); i++)
	  {
	    scores.push_back(p);
	  }
	return;
      }

    for (unsigned i = 0; i < score.size(); i++)
      {
	if (score.is_better_at(i, scores[i].first))
	  {
	    scores[i] = p;
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
