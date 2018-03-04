#include "create_model.h"
#include <stdlib.h>

static
int constant_fold_expr(Model *model, dslParser::ExprContext *expr);

static
int constant_fold_field(Component *comp,
			const std::vector<dslParser::Access_suffixContext *>& access_suffixes)
{
  auto name0 = access_suffixes[0]->ID()->getText();
  auto name1 = access_suffixes[1]->ID()->getText();
    
  //#print("constant fold in component " + str(names) + ", list = " + str(self.table_list));
  auto table = comp->find_table(name0);
  auto row = table->find_row_by_key(name1);
  if (! row)
    {
      fprintf(stderr, "failed to find row '%s' of table '%s'\n",
	      name1.c_str(), name0.c_str());
      table->dump();
      abort();
    }
  auto value = atoi(row->get(1)->string.c_str());
  printf("PDF TABLE LOOKUP[%s.%s] = %d\n", name0.c_str(), name1.c_str(), value);
  return value;
}

static
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


static
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

static
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
  if (comp->info->name == "board")
    {
      comp->info->fixed_position = new Point(0, 0, 0);
    }
    
  model->current_component = comp;
  
  for (auto p : props)
    {
      if (p->datasheet_prop().size() > 0)
	{
	  comp->info->has_data_sheet = true;
	}
      if (p->component_type)
	{
	  comp->info->component_type = destringify(p->component_type->getText());
	  //fprintf(stderr, "SAW COMPONENT TYPE: '%s'\n", comp->component_type.c_str());
	}
    }
  
  for (auto p : props)
    {
      if (p->pin_name())
	{
	  for (auto pin_name : p->pin_name()->ID())
	    {
	      std::string normalized_pin_name = normalize_ident(pin_name->getText());
	      //fprintf(stderr, "normalized to %s\n", normalized_pin_name.c_str());

	      auto info = new PinInfo(normalized_pin_name);
	      auto pin = comp->add_pin(info);
	      for (auto k : p->pin_prop())
		{
		  auto m = k->pinmode->getText();

		  if (m == "input")
		    pin->info->mode = PinInfo::Mode::INPUT;
		  else if (m == "output")
		    pin->info->mode = PinInfo::Mode::OUTPUT;
		  else if (m == "inout")
		    pin->info->mode = PinInfo::Mode::INOUT;
		  else if (m == "analog_ground")
		    pin->info->mode = PinInfo::Mode::ANALOG_GROUND;
		  else if (m == "digital_ground")
		    pin->info->mode = PinInfo::Mode::DIGITAL_GROUND;
		  else {
		    fprintf(stderr, "unrecognized mode: %s\n", m.c_str());
		    abort();
		  }
		}
	    }
	}    
    }
}

static
void add_datasheet_props(Component *comp, dslParser::ComponentContext *ctxt)
{
  for (auto p : ctxt->component_property())
    {
      process_datasheet_prop(comp, p->datasheet_prop());
    }
}


static
void process_location(Component *comp,
		      const std::vector<dslParser::Location_propContext *> &loc_prop_list)
{
  auto model = comp->model;

  for (auto loc : loc_prop_list)
    {
      model->current_component = comp;
      auto sx = constant_fold_expr(model, loc->expr()[0]);
      auto sy = constant_fold_expr(model, loc->expr()[1]);
      
      comp->info->fixed_position = new Point(sx, sy, 0);
      comp->transpose(*comp->info->fixed_position);
    }
}

static
void add_location(Component *comp, dslParser::ComponentContext *ctxt)
{
  for (auto p : ctxt->component_property())
    {
      process_location(comp, p->location_prop());
    }
}

static
void do_process_dimensions(Component *comp,
			   const std::vector<dslParser::Dim_propContext *> &dim_prop_list)
{
  assert(dim_prop_list.size() > 0);
  auto model = comp->model;
  model->current_component = comp;
  
  for (auto dim : dim_prop_list)
    {
      if (dim->width)
	{
	  comp->info->dim.x = constant_fold_expr(model, dim->width);
	}
      
      if (dim->height)
	{
	  comp->info->dim.y = constant_fold_expr(model, dim->height);
	}
      
      if (dim->layers)
	{
	  comp->info->dim.layer = constant_fold_expr(model, dim->layers);
	}
    }
    
  if (comp->info->name == "board")
    {
      model->board_dim = comp->info->dim;
    }
}


static
void add_dimensions(Component *comp, dslParser::ComponentContext *ctxt)
{
  for (auto p : ctxt->component_property())
    {
      if (p->dim_prop().size() > 0)
	{
	  do_process_dimensions(comp, p->dim_prop());
	}
    }
}

static
void process_component_type(Model *model,
			    Component *comp)
{  
  if (! comp->info->has_data_sheet)
    {
      if (comp->info->component_type != "")
	{
	  auto pkg = findKnownPackage(comp->info->component_type);
	  pkg->create_outline(comp);
	}
      else
	{
	  printf("COMPONENT %s has no assigned type yet\n", comp->info->name.c_str());
	  comp->outline.addRect(Point(0, 0, comp->info->dim.layer),
				Point(comp->info->dim.x, comp->info->dim.y, comp->info->dim.layer));
	}
    }
  else
    {
      fprintf(stderr, "component %s has a datasheet!\n", comp->info->name.c_str());
    }
}


void ModelCreatorListener::add_connections(ModelContext &mctxt, dslParser::NetworkContext *ctxt) {
  for (auto conn : ctxt->connection())
    {
      for (unsigned k = 0; k < conn->access().size()-1; k++)
	{
	  auto from_access = conn->access()[k];
	  auto to_access   = conn->access()[k + 1];
	  auto from_pin   = access_to_component_pin(this->model, from_access, mctxt, true);
	  auto to_pin     = access_to_component_pin(this->model, to_access, mctxt, false);
	  from_pin->add_connection(to_pin);
	}
    }
}


void ModelCreatorListener::enterConstant(dslParser::ConstantContext *ctxt) {
  //constant: 'const' ID '=' expr ';';
  auto name = ctxt->ID()->getText();
  auto expr = ctxt->expr();
  std::cout << "resolve constant: " << name;
  this->model->constants[name] = constant_fold_expr(this->model, expr);
}


void ModelCreatorListener::enterNetwork(dslParser::NetworkContext *ctxt) {
  auto names = ctxt->object_name()->ID();
  if (names.size() == 1)
    {
      ModelContext mctxt;
      this->add_connections(mctxt, ctxt);
    }
  else
    {
      auto limit = names[2]->getText();
      auto count = this->model->constants[limit];
      for (int i = 0; i < count; i++) {
	auto var = ModelVar(names[1]->getText(), i);
	ModelContext mctxt;
	mctxt.add(var);
	this->add_connections(mctxt, ctxt);
      }
    }
}




void ModelCreatorListener::enterComponent(dslParser::ComponentContext *ctxt)
{
  auto names = ctxt->object_name()->ID();
  //utils::print("EXAMINE COMPONENT: ", utils::str(names));
  if (names.size() == 1)
    {
      ComponentInfo *info = new ComponentInfo(names[0]->getText(), false);
      
      auto comp = new Component(info, this->model);
      preprocess_component(this->model, comp, ctxt->component_property());
      this->model->components.push_back(comp);
	
      add_dimensions(comp, ctxt);
      process_component_type(model, 
			     comp);
      add_datasheet_props(comp, ctxt);
      add_location(comp, ctxt);          
    }
  else
    {
      auto limit = names[2]->getText();
      auto count = this->model->constants[limit];
      for (int i = 0; i< count; i++)
	{
	  auto info = new ComponentInfo(names[0]->getText() + str(i), false);
	  
	  auto comp = new Component(info, this->model);
				    
	  preprocess_component(this->model, comp, ctxt->component_property());
	  this->model->components.push_back(comp);
	    
	  for (auto p : ctxt->component_property())
	    {
	      if (p->dim_prop().size() > 0)
		{
		  do_process_dimensions(comp, p->dim_prop());
		}	      
	    }
	  process_component_type(model,
				 comp);
	}
    }
}

