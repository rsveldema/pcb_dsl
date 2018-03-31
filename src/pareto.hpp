
struct ParetoFront
{
  std::map<unsigned, std::pair<score_t, Model *> > scores;

  void tryAddToFront(const score_t &score, Model *model)
  {    
    std::pair<score_t, Model *> p = {score, model};
    if (scores.size() == 0)
      {
	for (unsigned i = 0; i < score.size(); i++)
	  {
	    scores[i]    = p;
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
    for (auto it : scores)
      {
	selected[it.second.second] = true;
      }
  }
};
