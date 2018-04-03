
// Generated from /home/vagrant/Projects/pcb_dsl/src/dsl.antlr4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "dslListener.h"


namespace antlrcpp {

/**
 * This class provides an empty implementation of dslListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  dslBaseListener : public dslListener {
public:

  virtual void enterStartRule(dslParser::StartRuleContext * /*ctx*/) override { }
  virtual void exitStartRule(dslParser::StartRuleContext * /*ctx*/) override { }

  virtual void enterDirective(dslParser::DirectiveContext * /*ctx*/) override { }
  virtual void exitDirective(dslParser::DirectiveContext * /*ctx*/) override { }

  virtual void enterConstant(dslParser::ConstantContext * /*ctx*/) override { }
  virtual void exitConstant(dslParser::ConstantContext * /*ctx*/) override { }

  virtual void enterStrategy(dslParser::StrategyContext * /*ctx*/) override { }
  virtual void exitStrategy(dslParser::StrategyContext * /*ctx*/) override { }

  virtual void enterStrategy_property(dslParser::Strategy_propertyContext * /*ctx*/) override { }
  virtual void exitStrategy_property(dslParser::Strategy_propertyContext * /*ctx*/) override { }

  virtual void enterStrategy_foreach(dslParser::Strategy_foreachContext * /*ctx*/) override { }
  virtual void exitStrategy_foreach(dslParser::Strategy_foreachContext * /*ctx*/) override { }

  virtual void enterStrategy_call(dslParser::Strategy_callContext * /*ctx*/) override { }
  virtual void exitStrategy_call(dslParser::Strategy_callContext * /*ctx*/) override { }

  virtual void enterConstraint(dslParser::ConstraintContext * /*ctx*/) override { }
  virtual void exitConstraint(dslParser::ConstraintContext * /*ctx*/) override { }

  virtual void enterConstraint_property(dslParser::Constraint_propertyContext * /*ctx*/) override { }
  virtual void exitConstraint_property(dslParser::Constraint_propertyContext * /*ctx*/) override { }

  virtual void enterConstraint_foreach(dslParser::Constraint_foreachContext * /*ctx*/) override { }
  virtual void exitConstraint_foreach(dslParser::Constraint_foreachContext * /*ctx*/) override { }

  virtual void enterConstraint_if(dslParser::Constraint_ifContext * /*ctx*/) override { }
  virtual void exitConstraint_if(dslParser::Constraint_ifContext * /*ctx*/) override { }

  virtual void enterConstraint_require(dslParser::Constraint_requireContext * /*ctx*/) override { }
  virtual void exitConstraint_require(dslParser::Constraint_requireContext * /*ctx*/) override { }

  virtual void enterNetwork(dslParser::NetworkContext * /*ctx*/) override { }
  virtual void exitNetwork(dslParser::NetworkContext * /*ctx*/) override { }

  virtual void enterConnection(dslParser::ConnectionContext * /*ctx*/) override { }
  virtual void exitConnection(dslParser::ConnectionContext * /*ctx*/) override { }

  virtual void enterObject_name(dslParser::Object_nameContext * /*ctx*/) override { }
  virtual void exitObject_name(dslParser::Object_nameContext * /*ctx*/) override { }

  virtual void enterComponent(dslParser::ComponentContext * /*ctx*/) override { }
  virtual void exitComponent(dslParser::ComponentContext * /*ctx*/) override { }

  virtual void enterComponent_property(dslParser::Component_propertyContext * /*ctx*/) override { }
  virtual void exitComponent_property(dslParser::Component_propertyContext * /*ctx*/) override { }

  virtual void enterPin_name(dslParser::Pin_nameContext * /*ctx*/) override { }
  virtual void exitPin_name(dslParser::Pin_nameContext * /*ctx*/) override { }

  virtual void enterPin_prop(dslParser::Pin_propContext * /*ctx*/) override { }
  virtual void exitPin_prop(dslParser::Pin_propContext * /*ctx*/) override { }

  virtual void enterLocation_prop(dslParser::Location_propContext * /*ctx*/) override { }
  virtual void exitLocation_prop(dslParser::Location_propContext * /*ctx*/) override { }

  virtual void enterDatasheet_prop(dslParser::Datasheet_propContext * /*ctx*/) override { }
  virtual void exitDatasheet_prop(dslParser::Datasheet_propContext * /*ctx*/) override { }

  virtual void enterDim_prop(dslParser::Dim_propContext * /*ctx*/) override { }
  virtual void exitDim_prop(dslParser::Dim_propContext * /*ctx*/) override { }

  virtual void enterPrimary(dslParser::PrimaryContext * /*ctx*/) override { }
  virtual void exitPrimary(dslParser::PrimaryContext * /*ctx*/) override { }

  virtual void enterLen(dslParser::LenContext * /*ctx*/) override { }
  virtual void exitLen(dslParser::LenContext * /*ctx*/) override { }

  virtual void enterExpr(dslParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(dslParser::ExprContext * /*ctx*/) override { }

  virtual void enterOp(dslParser::OpContext * /*ctx*/) override { }
  virtual void exitOp(dslParser::OpContext * /*ctx*/) override { }

  virtual void enterAccess(dslParser::AccessContext * /*ctx*/) override { }
  virtual void exitAccess(dslParser::AccessContext * /*ctx*/) override { }

  virtual void enterAccess_suffix(dslParser::Access_suffixContext * /*ctx*/) override { }
  virtual void exitAccess_suffix(dslParser::Access_suffixContext * /*ctx*/) override { }

  virtual void enterIndex(dslParser::IndexContext * /*ctx*/) override { }
  virtual void exitIndex(dslParser::IndexContext * /*ctx*/) override { }

  virtual void enterUnit(dslParser::UnitContext * /*ctx*/) override { }
  virtual void exitUnit(dslParser::UnitContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace antlrcpp
