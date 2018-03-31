#include "model.hpp"


void Pin::check()
{
  if (outline.size() == 0)
    {
      fprintf(stderr, "ERROR: pin %s has no outline\n", info->name.c_str());
      abort();
    }
}


void Component::check()
{    
  if (bounding_box.size() == 0)
    {
      fprintf(stderr, "ERROR: component %s has no bounding box\n", info->name.c_str());
      abort();
    }
  if (outline.size() == 0)
    {
      fprintf(stderr, "ERROR: component %s has no outline\n", info->name.c_str());
      abort();
    }

  for (unsigned ci=0;ci<pins.size();ci++)
    {
      auto pin = pins[ci];
      pin->check();
    }
}


static
void check_unconnected_components(Model *model)
{
  std::map<Component*, bool> connected;
  
  for (auto c : model->components)
    {
      for (unsigned ci=0;ci<c->pins.size();ci++)
	{
	  auto pin = c->pins[ci];
	  
	  for (unsigned ix = 0; ix < pin->size(); ix++)
	    {
	      auto other_pin = pin->get(ix);
	      connected[c] = true;
	      connected[other_pin->component] = true;
	    }
	}
    }

  for (auto c : model->components)
    {
      if (c->info->is_board)
	{
	  // ignore, doesn't need to be connected to anything
	}
      else
	{
	  if (connected.find(c) == connected.end())
	    {
	      fprintf(stderr,
		      "component '%s' does not seem to be connected to anything!\n",
		      c->info->name.c_str());
	      abort();
	    }
	}
    }
}

void RuleExpr::check(Model *m,
		     bool root)
{
  if (lhs)
    {
      lhs->check(m, false);
    }
  if (rhs)
    {
      rhs->check(m, false);
    }

  if (! root)
    {
      switch (type)
	{
	default:
	  break;
	case LEN:
	  {
	    Pin *p1 = lhs->find_pin(m);
	    Pin *p2 = rhs->find_pin(m);

	    if (! p1->have_connection(p2))
	      {
		fprintf(stderr,
			"ERROR: no connection from %s to %s\n",
			p1->pretty().c_str(),
			p2->pretty().c_str());
		abort();
	      }
	    break;
	  }
	}
    }
  else
    {
      switch (type)
	{
	case EQ:
	case NEQ:
	  break;
	  
	default:
	  fprintf(stderr, "ERROR: bad constraint operator: %s\n", str().c_str());
	  abort();
	}
    }
}

void Constraint::check(Model *m)
{
  for (auto c : rules)
    {
      c->check(m, true);
    }
}

void Model::check()    
{
  check_unconnected_components(this);

  for (auto c : info->constraints)
    {
      c->check(this);
    }
  
  for (auto c : components)
    {
      c->check();
    }
}

