#include "create_model.h"
#include <algorithm>
#include "utils.h"

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
