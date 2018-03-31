#include "create_model.hpp"
#include <stdlib.h>

Pin *Component::find_pin_by_name(const std::string &name)
{
  const unsigned c = pins.size();
  for (unsigned i =  0; i < c; i++)
    {
      Pin *p = pins[i];
      if (p->info->name == name)
	{
	  return p;
	}
    }
  fprintf(stderr,
	  "failed to find pin %s in component %s\n",
	  name.c_str(),
	  info->name.c_str());
  abort();
}

Component *RuleExpr::find_component(Model *m)
{
  switch (type)
    {
    case COMP_ACCESS:
      {
	auto comp = m->find_component(name);
	return comp;
      }
    default:
      abort();
    }
  return NULL;
}

Pin *RuleExpr::find_pin(Model *m)
{
  switch (type)
    {
    case PIN_ACCESS:
      {
	auto comp = lhs->find_component(m);
	if (auto pin = comp->find_pin_by_name(name))
	  {
	    return pin;
	  }
	else
	  {
	    fprintf(stderr, "failed to find component %s from constraint\n",
		    name.c_str());
	    abort();
	  }
      }
      
    default:
      abort();
    }
  return NULL;
}

int64_t compute_distance(Pin *p1,
			 Pin *p2)
{
  for (unsigned i=0;i<p1->size();i++)
    {
      Pin *c = p1->get(i);
      if (c == p2)
	{
	  return p1->center().distance(p2->center());
	}
    }
  for (unsigned i=0;i<p1->size();i++)
    {
      Pin *c = p1->get(i);

      auto comp = c->component;
      assert(comp->info->is_router);
      
      for (auto other_pin : comp->pins)
	{
	  if (other_pin != c)
	    {
	      int64_t a = compute_distance(other_pin, p2);
	      if (a >= 0)
		{
		  int64_t k = p1->center().distance(c->center());
		  return a + k;
		}
	    }
	}
    }
  return -1;
}

int64_t RuleExpr::eval(Model *m)
{
  switch (type)
    {
    case INT_CONST: return iconst;
    case LEN:
      {
	Pin *p1 = lhs->find_pin(m);
	Pin *p2 = rhs->find_pin(m);
	int64_t ret = compute_distance(p1, p2);
	assert(ret >= 0);
	return ret;
      }
    default:
      abort();
    }
}

int RuleExpr::score(Model *m)
{
  int64_t a = lhs->eval(m);
  int64_t b = rhs->eval(m);
  
  switch (type)
    {
    case EQ:    return std::abs(a - b);
    case NEQ:   return a != b ? 0 : 1000;
    default:
      abort();
    }
}

void Constraint::score(Model *m,
		       score_data_t &result)
{
  const unsigned k = rules.size();
  for (unsigned i = 0; i < k; i++)
    {
      RuleExpr *r = rules[i];
      int32_t score = r->score(m);
      result.push_back(score);
    }
}
