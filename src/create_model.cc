#include "create_model.h"
#include <stdlib.h>

std::string destringify(const std::string &s)
{
  return s.substr(1, s.size()-2);
}



int constant_fold_field(Component *comp,
			const std::vector<dslParser::Access_suffixContext *>& access_suffixes)
{
  auto name0 = access_suffixes[0]->ID()->getText();
  auto name1 = access_suffixes[1]->ID()->getText();
    
  //#print("constant fold in component " + str(names) + ", list = " + str(self.table_list));
  auto table = comp->find_table(name0);
  auto row = table->find_row_by_key(name1);
  auto value = atoi(row->get(1)->string.c_str());
  printf("PDF TABLE LOOKUP[%s.%s] = %d\n", name0.c_str(), name1.c_str(), value);
  return value;
}

int constant_fold_access(Model *model, dslParser::AccessContext *access)
{
  auto name = access->ID()->getText();
  if (access->access_suffix().size() == 0)
    {
      if (access->index() == NULL)
	{
	  return model->constants[name];
	}
    }
  
  auto comp = model->find_component(name);
  if (comp)
    {
      return constant_fold_field(comp, access->access_suffix());
    }
  abort();
}

int constant_fold_primary(Model *model, dslParser::PrimaryContext *p)
{
  if (p->length)
    {
      auto name = p->ID()->getText();
      return model->current_component->resolve_length(name);
    }
  if (p->expr())
    {
      return constant_fold_expr(model, p->expr());
    }
  if (p->access())
    {
      return constant_fold_access(model, p->access());
    }
  auto unit = p->unit()->name->getText();
  auto value = atof(p->n->getText().c_str());
  if (unit == "cm")
    return value * 10;
  if (unit == "mm")
    return value;
  if (unit == "layer")
    return value;
  abort();
}

int constant_fold_expr(Model *model, dslParser::ExprContext *expr)
{
  auto p = expr->primary();
  auto left = constant_fold_primary(model, p[0]);
  if (p.size() == 1)
    {
      return left;
    }
  else
    {
      auto right = constant_fold_primary(model, p[1]);
      auto operand = expr->op()->operand->getText();
      if (operand == "+")
	return left + right;
      if (operand == "*")
	return left * right;
      if (operand == "/")
	return left / right;
      if (operand == "%")
	return left % right;
      abort();
    }
  return 0;
}

Pin *access_to_component_pin(Model *model,
			     dslParser::AccessContext* access,
			     ModelContext &context,
			     bool odd)
{
  auto name = access->ID()->getText();
  if (access->index())
    {
      name = context.indexed_comp_name(name, access->index());
    }
  
  auto comp = model->find_component(name);
  return comp->get_pin_by_suffixes(access->access_suffix(), context, odd);
}

void preprocess_component(Model *model,
			  Component *comp,
			  const std::vector<dslParser::Component_propertyContext *>& props)
{
  if (comp->name == "board")
    {
      comp->fixed_position = new Point(0, 0, 0);
    }
    
  model->current_component = comp;
  
  for (auto p : props)
    {
      if (p->datasheet_prop().size() > 0)
	{
	  comp->has_data_sheet = true;
	}
      if (p->component_type)
	{
	  comp->component_type = destringify(p->component_type->getText());
	  //#print("SAW COMPONENT TYPE: "+ comp->component_type)
	}
    }
  
  for (auto p : props)
    {
      if (p->pin_name())
	{
	  for (auto pin_name : p->pin_name()->ID())
	    {
	      auto pin = comp->add_pin(pin_name->getText());
	      for (auto k : p->pin_prop())
		{
		  pin->mode = k->pinmode->getText();
		}
	    }
	}    
    }
}

void add_dimensions(Component *comp, dslParser::ComponentContext *ctxt)
{
  for (auto p : ctxt->component_property())
    {
      process_dimensions(comp, p->dim_prop());
    }
}


void add_datasheet_props(Component *comp, dslParser::ComponentContext *ctxt)
{
  for (auto p : ctxt->component_property())
    {
      process_datasheet_prop(comp, p->datasheet_prop());
    }
}

void process_location(Component *comp,
		      const std::vector<dslParser::Location_propContext *> &loc_prop_list)
{
  auto model = comp->model;

  for (auto loc : loc_prop_list)
    {
      model->current_component = comp;
      auto sx = constant_fold_expr(model, loc->expr()[0]);
      auto sy = constant_fold_expr(model, loc->expr()[1]);
      
      comp->fixed_position = new Point(sx, sy, 0);
      comp->transpose(*comp->fixed_position);
    }
}

void add_location(Component *comp, dslParser::ComponentContext *ctxt)
{
  for (auto p : ctxt->component_property())
    {
      process_location(comp, p->location_prop());
    }
}

void process_dimensions(Component *comp,
			const std::vector<dslParser::Dim_propContext *> &dim_prop_list)
{
  if (dim_prop_list.size() == 0)
    {
      return;
    }
  auto model = comp->model;
  model->current_component = comp;
  
  for (auto dim : dim_prop_list)
    {
      if (dim->width)
	{
	  comp->dim.x = constant_fold_expr(model, dim->width);
	}
      
      if (dim->height)
	{
	  comp->dim.y = constant_fold_expr(model, dim->height);
	}
      
      if (dim->layers)
	{
	  comp->dim.layer = constant_fold_expr(model, dim->layers);
	}
    }

  if (comp->name == "board")
    {
      model->board_dim = comp->dim;
    }
  
  if (! comp->has_data_sheet)
    {
      if (comp->component_type != "")
	{
	  auto pkg = findKnownPackage(comp->component_type);
	  pkg->create_outline(comp);
	}
      else
	{
	  printf("COMPONENT %s has no assigned type yet\n", comp->name.c_str());
	  comp->outline.addRect(Point(0, 0, comp->dim.layer),
				Point(comp->dim.x, comp->dim.y, comp->dim.layer));
	}
    }
}
