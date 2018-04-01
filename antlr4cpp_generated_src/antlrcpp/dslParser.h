
// Generated from /home/devel/Projects/pcb_dsl/src/dsl.antlr4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"


namespace antlrcpp {


class  dslParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, T__55 = 56, 
    STRING = 57, ID = 58, NUMBER = 59, WS = 60, COMMENT = 61, LINE_COMMENT = 62
  };

  enum {
    RuleStartRule = 0, RuleDirective = 1, RuleConstant = 2, RuleStrategy = 3, 
    RuleStrategy_property = 4, RuleStrategy_foreach = 5, RuleStrategy_call = 6, 
    RuleConstraint = 7, RuleConstraint_property = 8, RuleConstraint_foreach = 9, 
    RuleConstraint_if = 10, RuleConstraint_require = 11, RuleNetwork = 12, 
    RuleConnection = 13, RuleObject_name = 14, RuleComponent = 15, RuleComponent_property = 16, 
    RulePin_name = 17, RulePin_prop = 18, RuleLocation_prop = 19, RuleDatasheet_prop = 20, 
    RuleDim_prop = 21, RulePrimary = 22, RuleLen = 23, RuleExpr = 24, RuleOp = 25, 
    RuleAccess = 26, RuleAccess_suffix = 27, RuleIndex = 28, RuleUnit = 29
  };

  dslParser(antlr4::TokenStream *input);
  ~dslParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class StartRuleContext;
  class DirectiveContext;
  class ConstantContext;
  class StrategyContext;
  class Strategy_propertyContext;
  class Strategy_foreachContext;
  class Strategy_callContext;
  class ConstraintContext;
  class Constraint_propertyContext;
  class Constraint_foreachContext;
  class Constraint_ifContext;
  class Constraint_requireContext;
  class NetworkContext;
  class ConnectionContext;
  class Object_nameContext;
  class ComponentContext;
  class Component_propertyContext;
  class Pin_nameContext;
  class Pin_propContext;
  class Location_propContext;
  class Datasheet_propContext;
  class Dim_propContext;
  class PrimaryContext;
  class LenContext;
  class ExprContext;
  class OpContext;
  class AccessContext;
  class Access_suffixContext;
  class IndexContext;
  class UnitContext; 

  class  StartRuleContext : public antlr4::ParserRuleContext {
  public:
    StartRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<DirectiveContext *> directive();
    DirectiveContext* directive(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StartRuleContext* startRule();

  class  DirectiveContext : public antlr4::ParserRuleContext {
  public:
    DirectiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ComponentContext *component();
    NetworkContext *network();
    ConstraintContext *constraint();
    StrategyContext *strategy();
    ConstantContext *constant();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DirectiveContext* directive();

  class  ConstantContext : public antlr4::ParserRuleContext {
  public:
    ConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantContext* constant();

  class  StrategyContext : public antlr4::ParserRuleContext {
  public:
    StrategyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    std::vector<Strategy_propertyContext *> strategy_property();
    Strategy_propertyContext* strategy_property(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StrategyContext* strategy();

  class  Strategy_propertyContext : public antlr4::ParserRuleContext {
  public:
    Strategy_propertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Strategy_foreachContext *strategy_foreach();
    Strategy_callContext *strategy_call();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Strategy_propertyContext* strategy_property();

  class  Strategy_foreachContext : public antlr4::ParserRuleContext {
  public:
    Strategy_foreachContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    ExprContext *expr();
    std::vector<Strategy_propertyContext *> strategy_property();
    Strategy_propertyContext* strategy_property(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Strategy_foreachContext* strategy_foreach();

  class  Strategy_callContext : public antlr4::ParserRuleContext {
  public:
    Strategy_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AccessContext *access();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Strategy_callContext* strategy_call();

  class  ConstraintContext : public antlr4::ParserRuleContext {
  public:
    ConstraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    std::vector<Constraint_propertyContext *> constraint_property();
    Constraint_propertyContext* constraint_property(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstraintContext* constraint();

  class  Constraint_propertyContext : public antlr4::ParserRuleContext {
  public:
    Constraint_propertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Constraint_foreachContext *constraint_foreach();
    Constraint_requireContext *constraint_require();
    Constraint_ifContext *constraint_if();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Constraint_propertyContext* constraint_property();

  class  Constraint_foreachContext : public antlr4::ParserRuleContext {
  public:
    Constraint_foreachContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    ExprContext *expr();
    std::vector<Constraint_propertyContext *> constraint_property();
    Constraint_propertyContext* constraint_property(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Constraint_foreachContext* constraint_foreach();

  class  Constraint_ifContext : public antlr4::ParserRuleContext {
  public:
    Constraint_ifContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    std::vector<Constraint_propertyContext *> constraint_property();
    Constraint_propertyContext* constraint_property(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Constraint_ifContext* constraint_if();

  class  Constraint_requireContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *prio = nullptr;;
    Constraint_requireContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Constraint_requireContext* constraint_require();

  class  NetworkContext : public antlr4::ParserRuleContext {
  public:
    NetworkContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Object_nameContext *object_name();
    std::vector<ConnectionContext *> connection();
    ConnectionContext* connection(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NetworkContext* network();

  class  ConnectionContext : public antlr4::ParserRuleContext {
  public:
    ConnectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AccessContext *> access();
    AccessContext* access(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConnectionContext* connection();

  class  Object_nameContext : public antlr4::ParserRuleContext {
  public:
    Object_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Object_nameContext* object_name();

  class  ComponentContext : public antlr4::ParserRuleContext {
  public:
    ComponentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Object_nameContext *object_name();
    std::vector<Component_propertyContext *> component_property();
    Component_propertyContext* component_property(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ComponentContext* component();

  class  Component_propertyContext : public antlr4::ParserRuleContext {
  public:
    dslParser::ExprContext *value = nullptr;;
    antlr4::Token *component_type = nullptr;;
    Component_propertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Dim_propContext *> dim_prop();
    Dim_propContext* dim_prop(size_t i);
    std::vector<Datasheet_propContext *> datasheet_prop();
    Datasheet_propContext* datasheet_prop(size_t i);
    Location_propContext *location_prop();
    Pin_nameContext *pin_name();
    std::vector<Pin_propContext *> pin_prop();
    Pin_propContext* pin_prop(size_t i);
    ExprContext *expr();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Component_propertyContext* component_property();

  class  Pin_nameContext : public antlr4::ParserRuleContext {
  public:
    Pin_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pin_nameContext* pin_name();

  class  Pin_propContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *pinmode = nullptr;;
    Pin_propContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pin_propContext* pin_prop();

  class  Location_propContext : public antlr4::ParserRuleContext {
  public:
    dslParser::ExprContext *x = nullptr;;
    dslParser::ExprContext *y = nullptr;;
    antlr4::Token *layer = nullptr;;
    antlr4::Token *rotatable = nullptr;;
    Location_propContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Location_propContext* location_prop();

  class  Datasheet_propContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *extractor = nullptr;;
    antlr4::Token *title = nullptr;;
    antlr4::Token *table = nullptr;;
    antlr4::Token *filename = nullptr;;
    Datasheet_propContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Datasheet_propContext* datasheet_prop();

  class  Dim_propContext : public antlr4::ParserRuleContext {
  public:
    dslParser::ExprContext *width = nullptr;;
    dslParser::ExprContext *height = nullptr;;
    dslParser::ExprContext *layers = nullptr;;
    Dim_propContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Dim_propContext* dim_prop();

  class  PrimaryContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *n = nullptr;;
    antlr4::Token *length = nullptr;;
    PrimaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnitContext *unit();
    antlr4::tree::TerminalNode *NUMBER();
    ExprContext *expr();
    AccessContext *access();
    antlr4::tree::TerminalNode *ID();
    LenContext *len();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryContext* primary();

  class  LenContext : public antlr4::ParserRuleContext {
  public:
    LenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AccessContext *> access();
    AccessContext* access(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LenContext* len();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PrimaryContext *> primary();
    PrimaryContext* primary(size_t i);
    OpContext *op();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();

  class  OpContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *operand = nullptr;;
    OpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OpContext* op();

  class  AccessContext : public antlr4::ParserRuleContext {
  public:
    AccessContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    IndexContext *index();
    std::vector<Access_suffixContext *> access_suffix();
    Access_suffixContext* access_suffix(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AccessContext* access();

  class  Access_suffixContext : public antlr4::ParserRuleContext {
  public:
    Access_suffixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    IndexContext *index();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Access_suffixContext* access_suffix();

  class  IndexContext : public antlr4::ParserRuleContext {
  public:
    IndexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IndexContext* index();

  class  UnitContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    UnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnitContext* unit();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace antlrcpp
