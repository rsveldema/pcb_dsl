#include "create_model.h"
#include <stdlib.h>

RuleExpr *create_rule(Model *model,
		      antlrcpp::dslParser::ExprContext* expr);


std::string RuleExpr::str() const
{
  switch (type)
    {
    case NONE: abort();
    case INT_CONST: {
      char buf[32];
      sprintf(buf, "%d", iconst);
      return buf;
    }
    case COMP_ACCESS:
      return name;
    case PIN_ACCESS:
      return lhs->str() + "." + name;
    case LEN:
      return "len("+lhs->str() + " -> " + rhs->str() + ")";
    case EQ:  return "("+lhs->str() + " == " + rhs->str() + ")";
    case NEQ: return "("+lhs->str() + " != " + rhs->str() + ")";
    case ADD: return "("+lhs->str() + " + " + rhs->str() + ")";
    case SUB: return "("+lhs->str() + " - " + rhs->str() + ")";
    case MUL: return "("+lhs->str() + " * " + rhs->str() + ")";
    case DIV: return "("+lhs->str() + " / " + rhs->str() + ")";
    }
  abort();
}


RuleExpr::RuleExpr(const std::string &op,
		   RuleExpr *lhs,
		   RuleExpr *rhs)
{
  this->lhs = lhs;
  this->rhs = rhs;
    
  if (op == "==")
    {
      type = EQ;
    }
  else if (op == "!=")
    {
      type = NEQ;
    }
  else if (op == "+")
    {
      type = ADD;
    }
  else if (op == "-")
    {
      type = SUB;
    }
  else if (op == "*")
    {
      type = MUL;
    }
  else if (op == "/")
    {
      type = DIV;
    }
  else
    {
      abort();
    }
}


/*
access: ID index? access_suffix*
access_suffix: ('.' ID index?)
index: '[' ID ']';
*/
RuleExpr *create_rule(Model *model,
		      antlrcpp::dslParser::AccessContext* expr)
{
  std::string ID = expr->ID()->getText();
  if (model->info->constants.find(ID) != model->info->constants.end())
    {
      int v = model->info->constants[ID];
      return new RuleExpr(v);
    }
 
  if (expr->index())
    {
      std::string loop_var = expr->index()->ID()->getText();
      if (model->info->constants.find(loop_var) == model->info->constants.end())
	{
	  fprintf(stderr, "failed to find loop var '%s'\n", loop_var.c_str());
	  abort();
	}
      
      int index_value = model->info->constants[loop_var];
      char buf[64];
      sprintf(buf, "%s%d",
	      ID.c_str(),
	      index_value);
      ID = buf;      
    }
  RuleExpr *a = new RuleExpr(ID);
  
  for (auto as : expr->access_suffix())
    {
      if (auto index = as->index())
	{
	  std::string loop_var = index->ID()->getText();
	  if (model->info->constants.find(loop_var) == model->info->constants.end())
	    {
	      fprintf(stderr, "failed to find loop var '%s'\n", loop_var.c_str());
	      abort();
	    }
	  
	  int index_value = model->info->constants[loop_var];
	  char buf[64];
	  sprintf(buf, "%s%d",
		  as->ID()->getText().c_str(),
		  index_value);
	  a = new RuleExpr(a, buf);
	}
      else
	{
	  a = new RuleExpr(a, as->ID()->getText());
	}
    }
  return a;
}

RuleExpr *create_rule(Model *model,
		      antlrcpp::dslParser::LenContext* expr)
{
  auto from = create_rule(model, expr->access()[0]);
  auto to   = create_rule(model, expr->access()[1]);
  return new RuleExpr(RuleExpr::LEN,
		      from,
		      to);
}

RuleExpr *create_rule(Model *model,
		      antlrcpp::dslParser::PrimaryContext* expr)
{
  if (expr->n)
    {
      int ret = constant_fold_primary(model, NULL, expr);
      return new RuleExpr(ret);
    }
  if (expr->expr())
    {
      return create_rule(model, expr->expr());
    }
  if (expr->access())
    {
      return create_rule(model, expr->access());
    }
  if (expr->len())
    {
      return create_rule(model, expr->len());
    }
  abort();
}

RuleExpr *create_rule(Model *model,
		      antlrcpp::dslParser::ExprContext* expr)
{
  if (expr->primary().size() == 1)
    {
      return create_rule(model, expr->primary()[0]);
    }
  else if (expr->primary().size() == 2)
    {
      RuleExpr *lhs = create_rule(model, expr->primary()[0]);
      RuleExpr *rhs = create_rule(model, expr->primary()[1]);

      std::string op = expr->op()->operand->getText().c_str();
      
      return new RuleExpr(op, lhs, rhs);
    }
  else
    {
      abort();
    }
  return 0;
}

void add_constraint(Constraint *c,
		    Model *model,
		    const std::vector<antlrcpp::dslParser::Constraint_propertyContext*> &code)
{
  for (auto p : code)
    {
      if (auto fe = p->constraint_foreach())
	{
	  std::string loop_var   = fe->ID()->getText().c_str();
	  auto loop_limit = fe->expr();
	  auto code       = fe->constraint_property();

	  auto v = constant_fold_expr(model,
				      NULL,//current_component,
				      loop_limit);//dslParser::ExprContext *expr);
	  fprintf(stderr, "loop-limit = %d\n", v);

	  for (int i = 0; i < v; i++)
	    {
	      model->info->constants[loop_var] = i;
	      add_constraint(c, model, code);
	    }
	}
      else if (auto cr = p->constraint_require())
	{
	  auto expr = cr->expr();
	  RuleExpr *r = create_rule(model, expr);
	  c->add(r);
	}
      else
	{
	  abort();
	}
    }
}

void ModelCreatorListener::enterConstraint(dslParser::ConstraintContext *ctxt)
{
  fprintf(stderr, "entering constraint %s\n", ctxt->ID()->getText().c_str());
  Constraint *c = new Constraint(ctxt->ID()->getText().c_str());

  add_constraint(c, model, ctxt->constraint_property());

  model->info->constraints.push_back(c);
}
