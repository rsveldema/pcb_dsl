
// Generated from /home/devel/Projects/pcb_dsl/src/dsl.antlr4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "dslParser.h"


namespace antlrcpp {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by dslParser.
 */
class  dslVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by dslParser.
   */
    virtual antlrcpp::Any visitStartRule(dslParser::StartRuleContext *context) = 0;

    virtual antlrcpp::Any visitDirective(dslParser::DirectiveContext *context) = 0;

    virtual antlrcpp::Any visitConstant(dslParser::ConstantContext *context) = 0;

    virtual antlrcpp::Any visitStrategy(dslParser::StrategyContext *context) = 0;

    virtual antlrcpp::Any visitStrategy_property(dslParser::Strategy_propertyContext *context) = 0;

    virtual antlrcpp::Any visitStrategy_foreach(dslParser::Strategy_foreachContext *context) = 0;

    virtual antlrcpp::Any visitStrategy_call(dslParser::Strategy_callContext *context) = 0;

    virtual antlrcpp::Any visitConstraint(dslParser::ConstraintContext *context) = 0;

    virtual antlrcpp::Any visitConstraint_property(dslParser::Constraint_propertyContext *context) = 0;

    virtual antlrcpp::Any visitConstraint_foreach(dslParser::Constraint_foreachContext *context) = 0;

    virtual antlrcpp::Any visitConstraint_if(dslParser::Constraint_ifContext *context) = 0;

    virtual antlrcpp::Any visitConstraint_require(dslParser::Constraint_requireContext *context) = 0;

    virtual antlrcpp::Any visitNetwork(dslParser::NetworkContext *context) = 0;

    virtual antlrcpp::Any visitConnection(dslParser::ConnectionContext *context) = 0;

    virtual antlrcpp::Any visitObject_name(dslParser::Object_nameContext *context) = 0;

    virtual antlrcpp::Any visitComponent(dslParser::ComponentContext *context) = 0;

    virtual antlrcpp::Any visitComponent_property(dslParser::Component_propertyContext *context) = 0;

    virtual antlrcpp::Any visitPin_name(dslParser::Pin_nameContext *context) = 0;

    virtual antlrcpp::Any visitPin_prop(dslParser::Pin_propContext *context) = 0;

    virtual antlrcpp::Any visitLocation_prop(dslParser::Location_propContext *context) = 0;

    virtual antlrcpp::Any visitDatasheet_prop(dslParser::Datasheet_propContext *context) = 0;

    virtual antlrcpp::Any visitDim_prop(dslParser::Dim_propContext *context) = 0;

    virtual antlrcpp::Any visitPrimary(dslParser::PrimaryContext *context) = 0;

    virtual antlrcpp::Any visitLen(dslParser::LenContext *context) = 0;

    virtual antlrcpp::Any visitExpr(dslParser::ExprContext *context) = 0;

    virtual antlrcpp::Any visitOp(dslParser::OpContext *context) = 0;

    virtual antlrcpp::Any visitAccess(dslParser::AccessContext *context) = 0;

    virtual antlrcpp::Any visitAccess_suffix(dslParser::Access_suffixContext *context) = 0;

    virtual antlrcpp::Any visitIndex(dslParser::IndexContext *context) = 0;

    virtual antlrcpp::Any visitUnit(dslParser::UnitContext *context) = 0;


};

}  // namespace antlrcpp
