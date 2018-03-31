#ifndef CREATE_MODEL_H___
#define CREATE_MODEL_H___

#include "parser.hpp"
#include "known_packages.hpp"
#include "model.hpp"

static inline
std::string str(int i)
{
  char buf[64];
  sprintf(buf, "%d", i);
  return buf;
}

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


void process_datasheet_prop(Model *model,
			    Component *comp,
			    const std::vector<dslParser::Datasheet_propContext *> &p);




class ModelCreatorListener : public dslBaseListener
{
 private:
  Model *model;
  Component *current_component = NULL;
  
 public:
  ModelCreatorListener()
    {
      ModelInfo *info = new ModelInfo();
      model = new Model(info);
    }

  Model *get() const { return model; }
  
 private:
  void add_connections(ModelContext &mctxt, dslParser::NetworkContext *ctxt);

 public:
  virtual void enterConstant(dslParser::ConstantContext *ctxt);
  virtual void enterNetwork(dslParser::NetworkContext *ctxt);
  virtual void enterComponent(dslParser::ComponentContext *ctxt);
  virtual void enterConstraint(dslParser::ConstraintContext *ctxt);
  void create_new_component(const std::string &name,
			    dslParser::ComponentContext *ctxt);
};


int constant_fold_expr(Model *model,
		       Component *current_component,
		       dslParser::ExprContext *expr);

int constant_fold_primary(Model *model,
			  Component *current_component,
			  dslParser::PrimaryContext *p);
#endif
