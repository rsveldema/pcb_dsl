
// Generated from /Users/dev/Projects/embedded/pcb_dsl/src/dsl.antlr4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "dslVisitor.h"


namespace antlrcpp {

/**
 * This class provides an empty implementation of dslVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class dslBaseVisitor : public dslVisitor {
public:

  virtual antlrcpp::Any visitStartRule(dslParser::StartRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDirective(dslParser::DirectiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstant(dslParser::ConstantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStrategy(dslParser::StrategyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStrategy_property(dslParser::Strategy_propertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStrategy_foreach(dslParser::Strategy_foreachContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStrategy_call(dslParser::Strategy_callContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstraint(dslParser::ConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstraint_property(dslParser::Constraint_propertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstraint_foreach(dslParser::Constraint_foreachContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstraint_require(dslParser::Constraint_requireContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNetwork(dslParser::NetworkContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConnection(dslParser::ConnectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitObject_name(dslParser::Object_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComponent(dslParser::ComponentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComponent_property(dslParser::Component_propertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPin_name(dslParser::Pin_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPin_prop(dslParser::Pin_propContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocation_prop(dslParser::Location_propContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatasheet_prop(dslParser::Datasheet_propContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDim_prop(dslParser::Dim_propContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimary(dslParser::PrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr(dslParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOp(dslParser::OpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAccess(dslParser::AccessContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAccess_suffix(dslParser::Access_suffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIndex(dslParser::IndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnit(dslParser::UnitContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace antlrcpp
