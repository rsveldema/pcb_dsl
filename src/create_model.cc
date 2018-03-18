#include "create_model.h"
#include <stdlib.h>

static constexpr double BOUNDING_BOX_MARGIN_MM = 0.5;

MillimeterPoint::MillimeterPoint(const Point &p)
  : x(((double)p.x) / Point::POINT_PRECISION),
    y(((double)p.y) / Point::POINT_PRECISION),
    layer(p.layer)
{
}



static
int constant_fold_expr(Model *model,
		       Component *current_component,
		       dslParser::ExprContext *expr);

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
	  return model->info->constants[name];
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
int constant_fold_primary(Model *model,
			  Component *current_component,
			  dslParser::PrimaryContext *p)
{
  if (p->length)
    {
      auto name = p->ID()->getText();
      return current_component->resolve_length(name);
    }
  if (p->expr())
    {
      return constant_fold_expr(model, current_component, p->expr());
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
int constant_fold_expr(Model *model,
		       Component *current_component,
		       dslParser::ExprContext *expr)
{
  auto p = expr->primary();
  auto left = constant_fold_primary(model, current_component, p[0]);
  if (p.size() == 1)
    {
      return left;
    }
  else
    {
      auto right = constant_fold_primary(model, current_component, p[1]);
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

   
Pin *Component::get_pin_by_name(const std::string &s)
{
  const unsigned count = pins.size();
  for (unsigned i=0;i<count;i++)
    {
      auto p = pins[i];
      
      if (p->info->name == s)
	{
	  return p;   
	}
    }
  fprintf(stderr, "failed to find pin %s\n", s.c_str());
  abort();
}

Pin *Component::get_pin_by_suffixes(const std::vector<dslParser::Access_suffixContext*> &suffixes,
				    ModelContext &context,
				    bool odd)
{
  if (suffixes.size() == 0)
    {
      if (pins.size() == 1)
	{
	  return pins[0];
	}
      
      if (pins.size() > 2)
	{
	  printf("don't know which pin to address, please make it explicit: %s\n", this->info->name.c_str());
	  abort();
	}    
      return pins[odd];
    }
  else
    {
      auto s0 = suffixes[0];
      auto name = s0->ID()->getText();
      if (s0->index() == 0)
	{
	  return get_pin_by_name(name);
	}
      else
	{
	  return get_pin_by_name(context.indexed_pin_name(name,
							  s0->index()));
	}
    }
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
  return comp->get_pin_by_suffixes(access->access_suffix(),
				   context,
				   odd);
}

void preprocess_component(Model *model,
			  Component *comp,
			  const std::vector<dslParser::Component_propertyContext *>& props)
{
  if (comp->info->name == "board")
    {
      comp->info->fixed_position = new Point;
    }
  
  //model->current_component = comp;
  
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
		      dslParser::Location_propContext * loc)
{
  if (!loc)
    {
      return;
    }
  
  auto model = comp->model;

  if (loc->rotatable)
    {
      comp->info->is_rotateable = true;
    }
  
  if (loc->x)
    {
      //model->current_component = comp;
      auto sx = constant_fold_expr(model, comp, loc->x);
      auto sy = constant_fold_expr(model, comp, loc->y);

      int layer = 0;
      if (loc->layer)
	{
	  layer = atoi(loc->layer->getText().c_str());
	}
	  
      // constant fold already changed every position to millimeters:
      comp->info->fixed_position = new Point(MillimeterPoint(sx,
							     sy,
							     layer));
      comp->transpose(*comp->info->fixed_position);
      comp->set_layer(layer);
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
  //model->current_component = comp;
  
  for (auto dim : dim_prop_list)
    {
      if (dim->width)
	{
	  comp->info->dim.x = constant_fold_expr(model, comp, dim->width);
	}
      
      if (dim->height)
	{
	  comp->info->dim.y = constant_fold_expr(model, comp, dim->height);
	}
      
      if (dim->layers)
	{
	  comp->info->dim.layer = constant_fold_expr(model, comp, dim->layers);
	}
    }
    
  if (comp->info->name == "board")
    {
      model->info->board_dim = comp->info->dim;
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
	  if (! comp->info->is_board)
	    {
	      printf("COMPONENT '%s' has no assigned type yet\n", comp->info->name.c_str());
	    }
	  comp->outline.addRect(Point(MillimeterPoint(0,
						      0,
						      comp->info->dim.layer)),
				Point(comp->info->dim));
	}
    }
  else
    {
      fprintf(stderr, "component %s has a datasheet!\n", comp->info->name.c_str());
    }
}


void ModelCreatorListener::add_connections(ModelContext &mctxt,
					   dslParser::NetworkContext *ctxt)
{
  for (auto conn : ctxt->connection())
    {
      for (unsigned k = 0; k < conn->access().size()-1; k++)
	{
	  auto from_access = conn->access()[k];
	  auto to_access   = conn->access()[k + 1];
	  auto from_pin   = access_to_component_pin(this->model,
						    from_access,
						    mctxt,
						    true); // odd
	  auto to_pin     = access_to_component_pin(this->model,
						    to_access,
						    mctxt,
						    false); // even

	  if (from_pin->get_layer() != to_pin->get_layer())
	    {
	      // connection of something on one layer to something
	      // on another layer. We hence must add a router.	      
	      Component *router = this->model->create_router(from_pin->center());
	      from_pin->add_connection(router->pins[0]);
	      router->pins[0]->set_layer(from_pin->get_layer());
	      
	      router->pins[1]->set_layer(to_pin->get_layer());
	      router->pins[1]->add_connection(to_pin);

	      assert(from_pin->get_layer() == router->pins[0]->get_layer());
	      assert(to_pin->get_layer()   == router->pins[1]->get_layer());	    
	    }
	  else
	    {
	      assert(from_pin->get_layer() == to_pin->get_layer());
	      from_pin->add_connection(to_pin);
	    }
	}
    }
}


void ModelCreatorListener::enterConstant(dslParser::ConstantContext *ctxt)
{
  //constant: 'const' ID '=' expr ';';
  auto name = ctxt->ID()->getText();
  auto expr = ctxt->expr();
  //std::cout << "resolve constant: " << name;
  assert(current_component);
  this->model->info->constants[name] = constant_fold_expr(this->model,
							  current_component,
							  expr);
}


void ModelCreatorListener::enterNetwork(dslParser::NetworkContext *ctxt)
{
  auto names = ctxt->object_name()->ID();
  if (names.size() == 1)
    {
      ModelContext mctxt;
      this->add_connections(mctxt, ctxt);
    }
  else
    {
      auto limit = names[2]->getText();
      auto count = this->model->info->constants[limit];
      for (int i = 0; i < count; i++) {
	auto var = ModelVar(names[1]->getText(), i);
	ModelContext mctxt;
	mctxt.add(var);
	this->add_connections(mctxt, ctxt);
      }
    }
}


void Component::add_bounding_box()
{
  min_max_t d;
  outline.minmax(d);
  for (auto p : pins)
    {
      p->outline.minmax(d);
    }

  MillimeterLength ml(BOUNDING_BOX_MARGIN_MM);

  d.min = d.min.sub(MillimeterPoint(ml, ml, d.min.layer));
  d.max = d.max.add(MillimeterPoint(ml, ml, d.min.layer));
  bounding_box.addRect(d.min, d.max);
  bounding_box.set_layer(outline.get_layer());
}


void ModelCreatorListener::enterComponent(dslParser::ComponentContext *ctxt)
{
  auto names = ctxt->object_name()->ID();
  //utils::print("EXAMINE COMPONENT: ", utils::str(names));
  if (names.size() == 1)
    {
      ComponentInfo *info = new ComponentInfo(names[0]->getText(), false);
      
      auto comp = new Component(info, this->model);
      this->current_component = comp;
      preprocess_component(this->model, comp, ctxt->component_property());
      this->model->components.push_back(comp);
	
      add_dimensions(comp, ctxt);
      process_component_type(model, 
			     comp);
      add_datasheet_props(comp, ctxt);
      add_location(comp, ctxt);
      comp->add_bounding_box();
    }
  else
    {
      auto limit = names[2]->getText();
      auto count = this->model->info->constants[limit];
      for (int i = 0; i< count; i++)
	{
	  auto info = new ComponentInfo(names[0]->getText() + str(i), false);
	  
	  auto comp = new Component(info, this->model);
	  this->current_component = comp;	    
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
	  comp->add_bounding_box();
	}
    }
}

