#include "model.h"


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
  
  for (auto c : pins)
    {
      c->check();
    }
}


static
void check_unconnected_components(Model *model)
{
  std::map<Component*, bool> connected;
  
  for (auto c : model->components)
    {
      for (auto pin : c->pins)
	{
	  for (auto other_pin : pin->connections)
	    {
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

void Model::check()    
{
  check_unconnected_components(this);
  
  for (auto c : components)
    {
      c->check();
    }
}

