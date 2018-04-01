
// Generated from /home/devel/Projects/pcb_dsl/src/dsl.antlr4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "dslParser.h"


namespace antlrcpp {

/**
 * This interface defines an abstract listener for a parse tree produced by dslParser.
 */
class  dslListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStartRule(dslParser::StartRuleContext *ctx) = 0;
  virtual void exitStartRule(dslParser::StartRuleContext *ctx) = 0;

  virtual void enterDirective(dslParser::DirectiveContext *ctx) = 0;
  virtual void exitDirective(dslParser::DirectiveContext *ctx) = 0;

  virtual void enterConstant(dslParser::ConstantContext *ctx) = 0;
  virtual void exitConstant(dslParser::ConstantContext *ctx) = 0;

  virtual void enterStrategy(dslParser::StrategyContext *ctx) = 0;
  virtual void exitStrategy(dslParser::StrategyContext *ctx) = 0;

  virtual void enterStrategy_property(dslParser::Strategy_propertyContext *ctx) = 0;
  virtual void exitStrategy_property(dslParser::Strategy_propertyContext *ctx) = 0;

  virtual void enterStrategy_foreach(dslParser::Strategy_foreachContext *ctx) = 0;
  virtual void exitStrategy_foreach(dslParser::Strategy_foreachContext *ctx) = 0;

  virtual void enterStrategy_call(dslParser::Strategy_callContext *ctx) = 0;
  virtual void exitStrategy_call(dslParser::Strategy_callContext *ctx) = 0;

  virtual void enterConstraint(dslParser::ConstraintContext *ctx) = 0;
  virtual void exitConstraint(dslParser::ConstraintContext *ctx) = 0;

  virtual void enterConstraint_property(dslParser::Constraint_propertyContext *ctx) = 0;
  virtual void exitConstraint_property(dslParser::Constraint_propertyContext *ctx) = 0;

  virtual void enterConstraint_foreach(dslParser::Constraint_foreachContext *ctx) = 0;
  virtual void exitConstraint_foreach(dslParser::Constraint_foreachContext *ctx) = 0;

  virtual void enterConstraint_if(dslParser::Constraint_ifContext *ctx) = 0;
  virtual void exitConstraint_if(dslParser::Constraint_ifContext *ctx) = 0;

  virtual void enterConstraint_require(dslParser::Constraint_requireContext *ctx) = 0;
  virtual void exitConstraint_require(dslParser::Constraint_requireContext *ctx) = 0;

  virtual void enterNetwork(dslParser::NetworkContext *ctx) = 0;
  virtual void exitNetwork(dslParser::NetworkContext *ctx) = 0;

  virtual void enterConnection(dslParser::ConnectionContext *ctx) = 0;
  virtual void exitConnection(dslParser::ConnectionContext *ctx) = 0;

  virtual void enterObject_name(dslParser::Object_nameContext *ctx) = 0;
  virtual void exitObject_name(dslParser::Object_nameContext *ctx) = 0;

  virtual void enterComponent(dslParser::ComponentContext *ctx) = 0;
  virtual void exitComponent(dslParser::ComponentContext *ctx) = 0;

  virtual void enterComponent_property(dslParser::Component_propertyContext *ctx) = 0;
  virtual void exitComponent_property(dslParser::Component_propertyContext *ctx) = 0;

  virtual void enterPin_name(dslParser::Pin_nameContext *ctx) = 0;
  virtual void exitPin_name(dslParser::Pin_nameContext *ctx) = 0;

  virtual void enterPin_prop(dslParser::Pin_propContext *ctx) = 0;
  virtual void exitPin_prop(dslParser::Pin_propContext *ctx) = 0;

  virtual void enterLocation_prop(dslParser::Location_propContext *ctx) = 0;
  virtual void exitLocation_prop(dslParser::Location_propContext *ctx) = 0;

  virtual void enterDatasheet_prop(dslParser::Datasheet_propContext *ctx) = 0;
  virtual void exitDatasheet_prop(dslParser::Datasheet_propContext *ctx) = 0;

  virtual void enterDim_prop(dslParser::Dim_propContext *ctx) = 0;
  virtual void exitDim_prop(dslParser::Dim_propContext *ctx) = 0;

  virtual void enterPrimary(dslParser::PrimaryContext *ctx) = 0;
  virtual void exitPrimary(dslParser::PrimaryContext *ctx) = 0;

  virtual void enterLen(dslParser::LenContext *ctx) = 0;
  virtual void exitLen(dslParser::LenContext *ctx) = 0;

  virtual void enterExpr(dslParser::ExprContext *ctx) = 0;
  virtual void exitExpr(dslParser::ExprContext *ctx) = 0;

  virtual void enterOp(dslParser::OpContext *ctx) = 0;
  virtual void exitOp(dslParser::OpContext *ctx) = 0;

  virtual void enterAccess(dslParser::AccessContext *ctx) = 0;
  virtual void exitAccess(dslParser::AccessContext *ctx) = 0;

  virtual void enterAccess_suffix(dslParser::Access_suffixContext *ctx) = 0;
  virtual void exitAccess_suffix(dslParser::Access_suffixContext *ctx) = 0;

  virtual void enterIndex(dslParser::IndexContext *ctx) = 0;
  virtual void exitIndex(dslParser::IndexContext *ctx) = 0;

  virtual void enterUnit(dslParser::UnitContext *ctx) = 0;
  virtual void exitUnit(dslParser::UnitContext *ctx) = 0;


};

}  // namespace antlrcpp
