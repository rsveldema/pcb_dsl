#ifndef CREATE_MODEL_H___
#define CREATE_MODEL_H___

#include "parser.h"
#include "database.h"
#include "model.h"

static inline
std::string str(int i)
{
  char buf[64];
  sprintf(buf, "%d", i);
  return buf;
}

int constant_fold_expr(Model *model, dslParser::ExprContext *expr);

class ModelVar {
 public:
  const std::string name;
  const int value;
  
 public:
  ModelVar(const std::string &_name,
	   const int &_value)
    : name(_name),
    value(_value)
    {
    }
};


class ModelContext
{
 private:
  std::vector<ModelVar> vars;

 public:
  void add(const std::string &var, int value) {
    this->vars.push_back(ModelVar(var, value));
  }

  void add(const ModelVar &v) {
    this->vars.push_back(v);
  }

  
  std::string indexed_comp_name(const std::string &name, dslParser::IndexContext* index) {
    for (auto v : this->vars) {
      if (v.name == index->ID()->getText()) {
	return name + str(v.value);
      }
    }
    abort();
    return "";
  }

  std::string indexed_pin_name(const std::string &name, dslParser::IndexContext* index) {
    for (auto v : this->vars) {
      //#print("EXAMINE " + v.name + " vs " + str(index.ID()))
      if (v.name == index->ID()->getText()) {
	return name + str(v.value);
      }
    }
    printf("ERRROR: failed to find %s\n", index->ID()->getText().c_str());
    abort();
    return "";
  }
};

void process_datasheet_prop(Component *comp,
			    const std::vector<dslParser::Datasheet_propContext *> &p);

Pin *access_to_component_pin(Model *model,
			     dslParser::AccessContext* access,
			     ModelContext &context,
			     bool odd);

void preprocess_component(Model *model,
			  Component *comp,
			  const std::vector<dslParser::Component_propertyContext *>& prop);

void add_dimensions(Component *comp, dslParser::ComponentContext *ctxt);
void add_datasheet_props(Component *comp, dslParser::ComponentContext *ctxt);
void add_location(Component *comp, dslParser::ComponentContext *ctxt);
void process_dimensions(Component *comp,
			const std::vector<dslParser::Dim_propContext *> &dim_prop_list);

class ModelCreatorListener : public dslBaseListener
{
 private:
  Model *model;
  
 public:
  ModelCreatorListener()
    {
      model = new Model();
    }

  Model *get() const { return model; }

  virtual void  enterConstant(dslParser::ConstantContext *ctxt) {
    //constant: 'const' ID '=' expr ';';
    auto name = ctxt->ID()->getText();
    auto expr = ctxt->expr();
    std::cout << "resolve constant: " << name;
    this->model->constants[name] = constant_fold_expr(this->model, expr);
  }
  
 private:

  void  add_connections(ModelContext &mctxt, dslParser::NetworkContext *ctxt) {
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

  virtual void  enterNetwork(dslParser::NetworkContext *ctxt) {
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

  virtual void  enterComponent(dslParser::ComponentContext *ctxt)
  {
    auto names = ctxt->object_name()->ID();
    //print("EXAMINE COMPONENT: " + str(names))
    if (names.size() == 1)
      {
	auto comp = new Component(this->model, names[0]->getText(), false);
	preprocess_component(this->model, comp, ctxt->component_property());
	this->model->components.push_back(comp);
	
	add_dimensions(comp, ctxt);
	add_datasheet_props(comp, ctxt);
	add_location(comp, ctxt);          
      }
    else
      {
	auto limit = names[2]->getText();
	auto count = this->model->constants[limit];
	for (int i = 0; i< count; i++)
	  {
	    auto comp = new Component(this->model,
				      names[0]->getText() + str(i), false);
	    preprocess_component(this->model, comp, ctxt->component_property());
	    this->model->components.push_back(comp);
	    
	    for (auto p : ctxt->component_property())
	      {
		process_dimensions(comp, p->dim_prop());
	      }
	  }
      }
  }
};

			  
#endif
