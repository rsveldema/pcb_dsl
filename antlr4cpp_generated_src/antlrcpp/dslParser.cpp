
// Generated from /home/vagrant/Projects/pcb_dsl/src/dsl.antlr4 by ANTLR 4.7.1


#include "dslListener.h"
#include "dslVisitor.h"

#include "dslParser.h"


using namespace antlrcpp;
using namespace antlrcpp;
using namespace antlr4;

dslParser::dslParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

dslParser::~dslParser() {
  delete _interpreter;
}

std::string dslParser::getGrammarFileName() const {
  return "dsl.antlr4";
}

const std::vector<std::string>& dslParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& dslParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- StartRuleContext ------------------------------------------------------------------

dslParser::StartRuleContext::StartRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* dslParser::StartRuleContext::EOF() {
  return getToken(dslParser::EOF, 0);
}

std::vector<dslParser::DirectiveContext *> dslParser::StartRuleContext::directive() {
  return getRuleContexts<dslParser::DirectiveContext>();
}

dslParser::DirectiveContext* dslParser::StartRuleContext::directive(size_t i) {
  return getRuleContext<dslParser::DirectiveContext>(i);
}


size_t dslParser::StartRuleContext::getRuleIndex() const {
  return dslParser::RuleStartRule;
}

void dslParser::StartRuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartRule(this);
}

void dslParser::StartRuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartRule(this);
}


antlrcpp::Any dslParser::StartRuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitStartRule(this);
  else
    return visitor->visitChildren(this);
}

dslParser::StartRuleContext* dslParser::startRule() {
  StartRuleContext *_localctx = _tracker.createInstance<StartRuleContext>(_ctx, getState());
  enterRule(_localctx, 0, dslParser::RuleStartRule);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << dslParser::T__0)
      | (1ULL << dslParser::T__3)
      | (1ULL << dslParser::T__10)
      | (1ULL << dslParser::T__15)
      | (1ULL << dslParser::T__18))) != 0)) {
      setState(60);
      directive();
      setState(65);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(66);
    match(dslParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DirectiveContext ------------------------------------------------------------------

dslParser::DirectiveContext::DirectiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

dslParser::ComponentContext* dslParser::DirectiveContext::component() {
  return getRuleContext<dslParser::ComponentContext>(0);
}

dslParser::NetworkContext* dslParser::DirectiveContext::network() {
  return getRuleContext<dslParser::NetworkContext>(0);
}

dslParser::ConstraintContext* dslParser::DirectiveContext::constraint() {
  return getRuleContext<dslParser::ConstraintContext>(0);
}

dslParser::StrategyContext* dslParser::DirectiveContext::strategy() {
  return getRuleContext<dslParser::StrategyContext>(0);
}

dslParser::ConstantContext* dslParser::DirectiveContext::constant() {
  return getRuleContext<dslParser::ConstantContext>(0);
}


size_t dslParser::DirectiveContext::getRuleIndex() const {
  return dslParser::RuleDirective;
}

void dslParser::DirectiveContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDirective(this);
}

void dslParser::DirectiveContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDirective(this);
}


antlrcpp::Any dslParser::DirectiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitDirective(this);
  else
    return visitor->visitChildren(this);
}

dslParser::DirectiveContext* dslParser::directive() {
  DirectiveContext *_localctx = _tracker.createInstance<DirectiveContext>(_ctx, getState());
  enterRule(_localctx, 2, dslParser::RuleDirective);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(73);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case dslParser::T__18: {
        enterOuterAlt(_localctx, 1);
        setState(68);
        component();
        break;
      }

      case dslParser::T__15: {
        enterOuterAlt(_localctx, 2);
        setState(69);
        network();
        break;
      }

      case dslParser::T__10: {
        enterOuterAlt(_localctx, 3);
        setState(70);
        constraint();
        break;
      }

      case dslParser::T__3: {
        enterOuterAlt(_localctx, 4);
        setState(71);
        strategy();
        break;
      }

      case dslParser::T__0: {
        enterOuterAlt(_localctx, 5);
        setState(72);
        constant();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantContext ------------------------------------------------------------------

dslParser::ConstantContext::ConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* dslParser::ConstantContext::ID() {
  return getToken(dslParser::ID, 0);
}

dslParser::ExprContext* dslParser::ConstantContext::expr() {
  return getRuleContext<dslParser::ExprContext>(0);
}


size_t dslParser::ConstantContext::getRuleIndex() const {
  return dslParser::RuleConstant;
}

void dslParser::ConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstant(this);
}

void dslParser::ConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstant(this);
}


antlrcpp::Any dslParser::ConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitConstant(this);
  else
    return visitor->visitChildren(this);
}

dslParser::ConstantContext* dslParser::constant() {
  ConstantContext *_localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
  enterRule(_localctx, 4, dslParser::RuleConstant);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(75);
    match(dslParser::T__0);
    setState(76);
    match(dslParser::ID);
    setState(77);
    match(dslParser::T__1);
    setState(78);
    expr();
    setState(79);
    match(dslParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StrategyContext ------------------------------------------------------------------

dslParser::StrategyContext::StrategyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* dslParser::StrategyContext::ID() {
  return getToken(dslParser::ID, 0);
}

std::vector<dslParser::Strategy_propertyContext *> dslParser::StrategyContext::strategy_property() {
  return getRuleContexts<dslParser::Strategy_propertyContext>();
}

dslParser::Strategy_propertyContext* dslParser::StrategyContext::strategy_property(size_t i) {
  return getRuleContext<dslParser::Strategy_propertyContext>(i);
}


size_t dslParser::StrategyContext::getRuleIndex() const {
  return dslParser::RuleStrategy;
}

void dslParser::StrategyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStrategy(this);
}

void dslParser::StrategyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStrategy(this);
}


antlrcpp::Any dslParser::StrategyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitStrategy(this);
  else
    return visitor->visitChildren(this);
}

dslParser::StrategyContext* dslParser::strategy() {
  StrategyContext *_localctx = _tracker.createInstance<StrategyContext>(_ctx, getState());
  enterRule(_localctx, 6, dslParser::RuleStrategy);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    match(dslParser::T__3);
    setState(82);
    match(dslParser::ID);
    setState(83);
    match(dslParser::T__4);
    setState(87);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == dslParser::T__6

    || _la == dslParser::ID) {
      setState(84);
      strategy_property();
      setState(89);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(90);
    match(dslParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Strategy_propertyContext ------------------------------------------------------------------

dslParser::Strategy_propertyContext::Strategy_propertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

dslParser::Strategy_foreachContext* dslParser::Strategy_propertyContext::strategy_foreach() {
  return getRuleContext<dslParser::Strategy_foreachContext>(0);
}

dslParser::Strategy_callContext* dslParser::Strategy_propertyContext::strategy_call() {
  return getRuleContext<dslParser::Strategy_callContext>(0);
}


size_t dslParser::Strategy_propertyContext::getRuleIndex() const {
  return dslParser::RuleStrategy_property;
}

void dslParser::Strategy_propertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStrategy_property(this);
}

void dslParser::Strategy_propertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStrategy_property(this);
}


antlrcpp::Any dslParser::Strategy_propertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitStrategy_property(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Strategy_propertyContext* dslParser::strategy_property() {
  Strategy_propertyContext *_localctx = _tracker.createInstance<Strategy_propertyContext>(_ctx, getState());
  enterRule(_localctx, 8, dslParser::RuleStrategy_property);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(94);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case dslParser::T__6: {
        enterOuterAlt(_localctx, 1);
        setState(92);
        strategy_foreach();
        break;
      }

      case dslParser::ID: {
        enterOuterAlt(_localctx, 2);
        setState(93);
        strategy_call();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Strategy_foreachContext ------------------------------------------------------------------

dslParser::Strategy_foreachContext::Strategy_foreachContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* dslParser::Strategy_foreachContext::ID() {
  return getToken(dslParser::ID, 0);
}

dslParser::ExprContext* dslParser::Strategy_foreachContext::expr() {
  return getRuleContext<dslParser::ExprContext>(0);
}

std::vector<dslParser::Strategy_propertyContext *> dslParser::Strategy_foreachContext::strategy_property() {
  return getRuleContexts<dslParser::Strategy_propertyContext>();
}

dslParser::Strategy_propertyContext* dslParser::Strategy_foreachContext::strategy_property(size_t i) {
  return getRuleContext<dslParser::Strategy_propertyContext>(i);
}


size_t dslParser::Strategy_foreachContext::getRuleIndex() const {
  return dslParser::RuleStrategy_foreach;
}

void dslParser::Strategy_foreachContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStrategy_foreach(this);
}

void dslParser::Strategy_foreachContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStrategy_foreach(this);
}


antlrcpp::Any dslParser::Strategy_foreachContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitStrategy_foreach(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Strategy_foreachContext* dslParser::strategy_foreach() {
  Strategy_foreachContext *_localctx = _tracker.createInstance<Strategy_foreachContext>(_ctx, getState());
  enterRule(_localctx, 10, dslParser::RuleStrategy_foreach);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    match(dslParser::T__6);
    setState(97);
    match(dslParser::ID);
    setState(98);
    match(dslParser::T__7);
    setState(99);
    expr();
    setState(100);
    match(dslParser::T__4);
    setState(104);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == dslParser::T__6

    || _la == dslParser::ID) {
      setState(101);
      strategy_property();
      setState(106);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(107);
    match(dslParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Strategy_callContext ------------------------------------------------------------------

dslParser::Strategy_callContext::Strategy_callContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

dslParser::AccessContext* dslParser::Strategy_callContext::access() {
  return getRuleContext<dslParser::AccessContext>(0);
}


size_t dslParser::Strategy_callContext::getRuleIndex() const {
  return dslParser::RuleStrategy_call;
}

void dslParser::Strategy_callContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStrategy_call(this);
}

void dslParser::Strategy_callContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStrategy_call(this);
}


antlrcpp::Any dslParser::Strategy_callContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitStrategy_call(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Strategy_callContext* dslParser::strategy_call() {
  Strategy_callContext *_localctx = _tracker.createInstance<Strategy_callContext>(_ctx, getState());
  enterRule(_localctx, 12, dslParser::RuleStrategy_call);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    access();
    setState(110);
    match(dslParser::T__8);
    setState(111);
    match(dslParser::T__9);
    setState(112);
    match(dslParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstraintContext ------------------------------------------------------------------

dslParser::ConstraintContext::ConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* dslParser::ConstraintContext::ID() {
  return getToken(dslParser::ID, 0);
}

std::vector<dslParser::Constraint_propertyContext *> dslParser::ConstraintContext::constraint_property() {
  return getRuleContexts<dslParser::Constraint_propertyContext>();
}

dslParser::Constraint_propertyContext* dslParser::ConstraintContext::constraint_property(size_t i) {
  return getRuleContext<dslParser::Constraint_propertyContext>(i);
}


size_t dslParser::ConstraintContext::getRuleIndex() const {
  return dslParser::RuleConstraint;
}

void dslParser::ConstraintContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraint(this);
}

void dslParser::ConstraintContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraint(this);
}


antlrcpp::Any dslParser::ConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitConstraint(this);
  else
    return visitor->visitChildren(this);
}

dslParser::ConstraintContext* dslParser::constraint() {
  ConstraintContext *_localctx = _tracker.createInstance<ConstraintContext>(_ctx, getState());
  enterRule(_localctx, 14, dslParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    match(dslParser::T__10);
    setState(115);
    match(dslParser::ID);
    setState(116);
    match(dslParser::T__4);
    setState(120);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << dslParser::T__6)
      | (1ULL << dslParser::T__11)
      | (1ULL << dslParser::T__12))) != 0)) {
      setState(117);
      constraint_property();
      setState(122);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(123);
    match(dslParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Constraint_propertyContext ------------------------------------------------------------------

dslParser::Constraint_propertyContext::Constraint_propertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

dslParser::Constraint_foreachContext* dslParser::Constraint_propertyContext::constraint_foreach() {
  return getRuleContext<dslParser::Constraint_foreachContext>(0);
}

dslParser::Constraint_requireContext* dslParser::Constraint_propertyContext::constraint_require() {
  return getRuleContext<dslParser::Constraint_requireContext>(0);
}

dslParser::Constraint_ifContext* dslParser::Constraint_propertyContext::constraint_if() {
  return getRuleContext<dslParser::Constraint_ifContext>(0);
}


size_t dslParser::Constraint_propertyContext::getRuleIndex() const {
  return dslParser::RuleConstraint_property;
}

void dslParser::Constraint_propertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraint_property(this);
}

void dslParser::Constraint_propertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraint_property(this);
}


antlrcpp::Any dslParser::Constraint_propertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitConstraint_property(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Constraint_propertyContext* dslParser::constraint_property() {
  Constraint_propertyContext *_localctx = _tracker.createInstance<Constraint_propertyContext>(_ctx, getState());
  enterRule(_localctx, 16, dslParser::RuleConstraint_property);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(128);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case dslParser::T__6: {
        enterOuterAlt(_localctx, 1);
        setState(125);
        constraint_foreach();
        break;
      }

      case dslParser::T__12: {
        enterOuterAlt(_localctx, 2);
        setState(126);
        constraint_require();
        break;
      }

      case dslParser::T__11: {
        enterOuterAlt(_localctx, 3);
        setState(127);
        constraint_if();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Constraint_foreachContext ------------------------------------------------------------------

dslParser::Constraint_foreachContext::Constraint_foreachContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* dslParser::Constraint_foreachContext::ID() {
  return getToken(dslParser::ID, 0);
}

dslParser::ExprContext* dslParser::Constraint_foreachContext::expr() {
  return getRuleContext<dslParser::ExprContext>(0);
}

std::vector<dslParser::Constraint_propertyContext *> dslParser::Constraint_foreachContext::constraint_property() {
  return getRuleContexts<dslParser::Constraint_propertyContext>();
}

dslParser::Constraint_propertyContext* dslParser::Constraint_foreachContext::constraint_property(size_t i) {
  return getRuleContext<dslParser::Constraint_propertyContext>(i);
}


size_t dslParser::Constraint_foreachContext::getRuleIndex() const {
  return dslParser::RuleConstraint_foreach;
}

void dslParser::Constraint_foreachContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraint_foreach(this);
}

void dslParser::Constraint_foreachContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraint_foreach(this);
}


antlrcpp::Any dslParser::Constraint_foreachContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitConstraint_foreach(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Constraint_foreachContext* dslParser::constraint_foreach() {
  Constraint_foreachContext *_localctx = _tracker.createInstance<Constraint_foreachContext>(_ctx, getState());
  enterRule(_localctx, 18, dslParser::RuleConstraint_foreach);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    match(dslParser::T__6);
    setState(131);
    match(dslParser::ID);
    setState(132);
    match(dslParser::T__7);
    setState(133);
    expr();
    setState(134);
    match(dslParser::T__4);
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << dslParser::T__6)
      | (1ULL << dslParser::T__11)
      | (1ULL << dslParser::T__12))) != 0)) {
      setState(135);
      constraint_property();
      setState(140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(141);
    match(dslParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Constraint_ifContext ------------------------------------------------------------------

dslParser::Constraint_ifContext::Constraint_ifContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

dslParser::ExprContext* dslParser::Constraint_ifContext::expr() {
  return getRuleContext<dslParser::ExprContext>(0);
}

std::vector<dslParser::Constraint_propertyContext *> dslParser::Constraint_ifContext::constraint_property() {
  return getRuleContexts<dslParser::Constraint_propertyContext>();
}

dslParser::Constraint_propertyContext* dslParser::Constraint_ifContext::constraint_property(size_t i) {
  return getRuleContext<dslParser::Constraint_propertyContext>(i);
}


size_t dslParser::Constraint_ifContext::getRuleIndex() const {
  return dslParser::RuleConstraint_if;
}

void dslParser::Constraint_ifContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraint_if(this);
}

void dslParser::Constraint_ifContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraint_if(this);
}


antlrcpp::Any dslParser::Constraint_ifContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitConstraint_if(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Constraint_ifContext* dslParser::constraint_if() {
  Constraint_ifContext *_localctx = _tracker.createInstance<Constraint_ifContext>(_ctx, getState());
  enterRule(_localctx, 20, dslParser::RuleConstraint_if);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    match(dslParser::T__11);
    setState(144);
    expr();
    setState(145);
    match(dslParser::T__4);
    setState(149);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << dslParser::T__6)
      | (1ULL << dslParser::T__11)
      | (1ULL << dslParser::T__12))) != 0)) {
      setState(146);
      constraint_property();
      setState(151);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(152);
    match(dslParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Constraint_requireContext ------------------------------------------------------------------

dslParser::Constraint_requireContext::Constraint_requireContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

dslParser::ExprContext* dslParser::Constraint_requireContext::expr() {
  return getRuleContext<dslParser::ExprContext>(0);
}

tree::TerminalNode* dslParser::Constraint_requireContext::NUMBER() {
  return getToken(dslParser::NUMBER, 0);
}


size_t dslParser::Constraint_requireContext::getRuleIndex() const {
  return dslParser::RuleConstraint_require;
}

void dslParser::Constraint_requireContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraint_require(this);
}

void dslParser::Constraint_requireContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraint_require(this);
}


antlrcpp::Any dslParser::Constraint_requireContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitConstraint_require(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Constraint_requireContext* dslParser::constraint_require() {
  Constraint_requireContext *_localctx = _tracker.createInstance<Constraint_requireContext>(_ctx, getState());
  enterRule(_localctx, 22, dslParser::RuleConstraint_require);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    match(dslParser::T__12);
    setState(155);
    match(dslParser::T__13);
    setState(156);
    dynamic_cast<Constraint_requireContext *>(_localctx)->prio = match(dslParser::NUMBER);
    setState(157);
    match(dslParser::T__14);
    setState(158);
    expr();
    setState(159);
    match(dslParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NetworkContext ------------------------------------------------------------------

dslParser::NetworkContext::NetworkContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

dslParser::Object_nameContext* dslParser::NetworkContext::object_name() {
  return getRuleContext<dslParser::Object_nameContext>(0);
}

std::vector<dslParser::ConnectionContext *> dslParser::NetworkContext::connection() {
  return getRuleContexts<dslParser::ConnectionContext>();
}

dslParser::ConnectionContext* dslParser::NetworkContext::connection(size_t i) {
  return getRuleContext<dslParser::ConnectionContext>(i);
}


size_t dslParser::NetworkContext::getRuleIndex() const {
  return dslParser::RuleNetwork;
}

void dslParser::NetworkContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNetwork(this);
}

void dslParser::NetworkContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNetwork(this);
}


antlrcpp::Any dslParser::NetworkContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitNetwork(this);
  else
    return visitor->visitChildren(this);
}

dslParser::NetworkContext* dslParser::network() {
  NetworkContext *_localctx = _tracker.createInstance<NetworkContext>(_ctx, getState());
  enterRule(_localctx, 24, dslParser::RuleNetwork);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    match(dslParser::T__15);
    setState(162);
    object_name();
    setState(163);
    match(dslParser::T__4);
    setState(167);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == dslParser::ID) {
      setState(164);
      connection();
      setState(169);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(170);
    match(dslParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConnectionContext ------------------------------------------------------------------

dslParser::ConnectionContext::ConnectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<dslParser::AccessContext *> dslParser::ConnectionContext::access() {
  return getRuleContexts<dslParser::AccessContext>();
}

dslParser::AccessContext* dslParser::ConnectionContext::access(size_t i) {
  return getRuleContext<dslParser::AccessContext>(i);
}


size_t dslParser::ConnectionContext::getRuleIndex() const {
  return dslParser::RuleConnection;
}

void dslParser::ConnectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConnection(this);
}

void dslParser::ConnectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConnection(this);
}


antlrcpp::Any dslParser::ConnectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitConnection(this);
  else
    return visitor->visitChildren(this);
}

dslParser::ConnectionContext* dslParser::connection() {
  ConnectionContext *_localctx = _tracker.createInstance<ConnectionContext>(_ctx, getState());
  enterRule(_localctx, 26, dslParser::RuleConnection);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(172);
    access();
    setState(175); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(173);
      match(dslParser::T__16);
      setState(174);
      access();
      setState(177); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == dslParser::T__16);
    setState(179);
    match(dslParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Object_nameContext ------------------------------------------------------------------

dslParser::Object_nameContext::Object_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> dslParser::Object_nameContext::ID() {
  return getTokens(dslParser::ID);
}

tree::TerminalNode* dslParser::Object_nameContext::ID(size_t i) {
  return getToken(dslParser::ID, i);
}


size_t dslParser::Object_nameContext::getRuleIndex() const {
  return dslParser::RuleObject_name;
}

void dslParser::Object_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObject_name(this);
}

void dslParser::Object_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObject_name(this);
}


antlrcpp::Any dslParser::Object_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitObject_name(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Object_nameContext* dslParser::object_name() {
  Object_nameContext *_localctx = _tracker.createInstance<Object_nameContext>(_ctx, getState());
  enterRule(_localctx, 28, dslParser::RuleObject_name);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(181);
    match(dslParser::ID);
    setState(187);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == dslParser::T__13) {
      setState(182);
      match(dslParser::T__13);
      setState(183);
      match(dslParser::ID);
      setState(184);
      match(dslParser::T__17);
      setState(185);
      match(dslParser::ID);
      setState(186);
      match(dslParser::T__14);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentContext ------------------------------------------------------------------

dslParser::ComponentContext::ComponentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

dslParser::Object_nameContext* dslParser::ComponentContext::object_name() {
  return getRuleContext<dslParser::Object_nameContext>(0);
}

std::vector<dslParser::Component_propertyContext *> dslParser::ComponentContext::component_property() {
  return getRuleContexts<dslParser::Component_propertyContext>();
}

dslParser::Component_propertyContext* dslParser::ComponentContext::component_property(size_t i) {
  return getRuleContext<dslParser::Component_propertyContext>(i);
}


size_t dslParser::ComponentContext::getRuleIndex() const {
  return dslParser::RuleComponent;
}

void dslParser::ComponentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponent(this);
}

void dslParser::ComponentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponent(this);
}


antlrcpp::Any dslParser::ComponentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitComponent(this);
  else
    return visitor->visitChildren(this);
}

dslParser::ComponentContext* dslParser::component() {
  ComponentContext *_localctx = _tracker.createInstance<ComponentContext>(_ctx, getState());
  enterRule(_localctx, 30, dslParser::RuleComponent);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    match(dslParser::T__18);
    setState(190);
    object_name();
    setState(191);
    match(dslParser::T__4);
    setState(195);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << dslParser::T__2)
      | (1ULL << dslParser::T__19)
      | (1ULL << dslParser::T__20)
      | (1ULL << dslParser::T__21)
      | (1ULL << dslParser::T__22)
      | (1ULL << dslParser::T__23)
      | (1ULL << dslParser::T__29)
      | (1ULL << dslParser::T__31))) != 0)) {
      setState(192);
      component_property();
      setState(197);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(198);
    match(dslParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Component_propertyContext ------------------------------------------------------------------

dslParser::Component_propertyContext::Component_propertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<dslParser::Dim_propContext *> dslParser::Component_propertyContext::dim_prop() {
  return getRuleContexts<dslParser::Dim_propContext>();
}

dslParser::Dim_propContext* dslParser::Component_propertyContext::dim_prop(size_t i) {
  return getRuleContext<dslParser::Dim_propContext>(i);
}

std::vector<dslParser::Datasheet_propContext *> dslParser::Component_propertyContext::datasheet_prop() {
  return getRuleContexts<dslParser::Datasheet_propContext>();
}

dslParser::Datasheet_propContext* dslParser::Component_propertyContext::datasheet_prop(size_t i) {
  return getRuleContext<dslParser::Datasheet_propContext>(i);
}

dslParser::Location_propContext* dslParser::Component_propertyContext::location_prop() {
  return getRuleContext<dslParser::Location_propContext>(0);
}

dslParser::Pin_nameContext* dslParser::Component_propertyContext::pin_name() {
  return getRuleContext<dslParser::Pin_nameContext>(0);
}

std::vector<dslParser::Pin_propContext *> dslParser::Component_propertyContext::pin_prop() {
  return getRuleContexts<dslParser::Pin_propContext>();
}

dslParser::Pin_propContext* dslParser::Component_propertyContext::pin_prop(size_t i) {
  return getRuleContext<dslParser::Pin_propContext>(i);
}

dslParser::ExprContext* dslParser::Component_propertyContext::expr() {
  return getRuleContext<dslParser::ExprContext>(0);
}

tree::TerminalNode* dslParser::Component_propertyContext::STRING() {
  return getToken(dslParser::STRING, 0);
}


size_t dslParser::Component_propertyContext::getRuleIndex() const {
  return dslParser::RuleComponent_property;
}

void dslParser::Component_propertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComponent_property(this);
}

void dslParser::Component_propertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComponent_property(this);
}


antlrcpp::Any dslParser::Component_propertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitComponent_property(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Component_propertyContext* dslParser::component_property() {
  Component_propertyContext *_localctx = _tracker.createInstance<Component_propertyContext>(_ctx, getState());
  enterRule(_localctx, 32, dslParser::RuleComponent_property);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(239);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case dslParser::T__19: {
        enterOuterAlt(_localctx, 1);
        setState(200);
        match(dslParser::T__19);
        setState(201);
        match(dslParser::T__4);
        setState(205);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << dslParser::T__35)
          | (1ULL << dslParser::T__36)
          | (1ULL << dslParser::T__37))) != 0)) {
          setState(202);
          dim_prop();
          setState(207);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(208);
        match(dslParser::T__5);
        break;
      }

      case dslParser::T__20: {
        enterOuterAlt(_localctx, 2);
        setState(209);
        match(dslParser::T__20);
        setState(210);
        match(dslParser::T__4);
        setState(214);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == dslParser::T__32

        || _la == dslParser::T__34) {
          setState(211);
          datasheet_prop();
          setState(216);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(217);
        match(dslParser::T__5);
        break;
      }

      case dslParser::T__2:
      case dslParser::T__29:
      case dslParser::T__31: {
        enterOuterAlt(_localctx, 3);
        setState(218);
        location_prop();
        break;
      }

      case dslParser::T__21: {
        enterOuterAlt(_localctx, 4);
        setState(219);
        match(dslParser::T__21);
        setState(220);
        pin_name();
        setState(221);
        match(dslParser::T__4);
        setState(225);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << dslParser::T__25)
          | (1ULL << dslParser::T__26)
          | (1ULL << dslParser::T__27)
          | (1ULL << dslParser::T__28))) != 0)) {
          setState(222);
          pin_prop();
          setState(227);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(228);
        match(dslParser::T__5);
        break;
      }

      case dslParser::T__22: {
        enterOuterAlt(_localctx, 5);
        setState(230);
        match(dslParser::T__22);
        setState(231);
        match(dslParser::T__17);
        setState(232);
        dynamic_cast<Component_propertyContext *>(_localctx)->value = expr();
        setState(233);
        match(dslParser::T__2);
        break;
      }

      case dslParser::T__23: {
        enterOuterAlt(_localctx, 6);
        setState(235);
        match(dslParser::T__23);
        setState(236);
        match(dslParser::T__17);
        setState(237);
        dynamic_cast<Component_propertyContext *>(_localctx)->component_type = match(dslParser::STRING);
        setState(238);
        match(dslParser::T__2);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pin_nameContext ------------------------------------------------------------------

dslParser::Pin_nameContext::Pin_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> dslParser::Pin_nameContext::ID() {
  return getTokens(dslParser::ID);
}

tree::TerminalNode* dslParser::Pin_nameContext::ID(size_t i) {
  return getToken(dslParser::ID, i);
}


size_t dslParser::Pin_nameContext::getRuleIndex() const {
  return dslParser::RulePin_name;
}

void dslParser::Pin_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPin_name(this);
}

void dslParser::Pin_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPin_name(this);
}


antlrcpp::Any dslParser::Pin_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitPin_name(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Pin_nameContext* dslParser::pin_name() {
  Pin_nameContext *_localctx = _tracker.createInstance<Pin_nameContext>(_ctx, getState());
  enterRule(_localctx, 34, dslParser::RulePin_name);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(241);
    match(dslParser::ID);
    setState(246);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == dslParser::T__24) {
      setState(242);
      match(dslParser::T__24);
      setState(243);
      match(dslParser::ID);
      setState(248);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pin_propContext ------------------------------------------------------------------

dslParser::Pin_propContext::Pin_propContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t dslParser::Pin_propContext::getRuleIndex() const {
  return dslParser::RulePin_prop;
}

void dslParser::Pin_propContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPin_prop(this);
}

void dslParser::Pin_propContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPin_prop(this);
}


antlrcpp::Any dslParser::Pin_propContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitPin_prop(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Pin_propContext* dslParser::pin_prop() {
  Pin_propContext *_localctx = _tracker.createInstance<Pin_propContext>(_ctx, getState());
  enterRule(_localctx, 36, dslParser::RulePin_prop);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(253);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case dslParser::T__25: {
        setState(249);
        dynamic_cast<Pin_propContext *>(_localctx)->pinmode = match(dslParser::T__25);
        break;
      }

      case dslParser::T__26: {
        setState(250);
        dynamic_cast<Pin_propContext *>(_localctx)->pinmode = match(dslParser::T__26);
        break;
      }

      case dslParser::T__27: {
        setState(251);
        dynamic_cast<Pin_propContext *>(_localctx)->pinmode = match(dslParser::T__27);
        break;
      }

      case dslParser::T__28: {
        setState(252);
        dynamic_cast<Pin_propContext *>(_localctx)->pinmode = match(dslParser::T__28);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(255);
    match(dslParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Location_propContext ------------------------------------------------------------------

dslParser::Location_propContext::Location_propContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<dslParser::ExprContext *> dslParser::Location_propContext::expr() {
  return getRuleContexts<dslParser::ExprContext>();
}

dslParser::ExprContext* dslParser::Location_propContext::expr(size_t i) {
  return getRuleContext<dslParser::ExprContext>(i);
}

tree::TerminalNode* dslParser::Location_propContext::NUMBER() {
  return getToken(dslParser::NUMBER, 0);
}


size_t dslParser::Location_propContext::getRuleIndex() const {
  return dslParser::RuleLocation_prop;
}

void dslParser::Location_propContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocation_prop(this);
}

void dslParser::Location_propContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocation_prop(this);
}


antlrcpp::Any dslParser::Location_propContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitLocation_prop(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Location_propContext* dslParser::location_prop() {
  Location_propContext *_localctx = _tracker.createInstance<Location_propContext>(_ctx, getState());
  enterRule(_localctx, 38, dslParser::RuleLocation_prop);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(266);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == dslParser::T__29) {
      setState(257);
      match(dslParser::T__29);
      setState(258);
      match(dslParser::T__17);
      setState(259);
      dynamic_cast<Location_propContext *>(_localctx)->x = expr();
      setState(260);
      match(dslParser::T__24);
      setState(261);
      dynamic_cast<Location_propContext *>(_localctx)->y = expr();
      setState(264);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == dslParser::T__30) {
        setState(262);
        match(dslParser::T__30);
        setState(263);
        dynamic_cast<Location_propContext *>(_localctx)->layer = match(dslParser::NUMBER);
      }
    }
    setState(269);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == dslParser::T__31) {
      setState(268);
      dynamic_cast<Location_propContext *>(_localctx)->rotatable = match(dslParser::T__31);
    }
    setState(271);
    match(dslParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Datasheet_propContext ------------------------------------------------------------------

dslParser::Datasheet_propContext::Datasheet_propContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> dslParser::Datasheet_propContext::ID() {
  return getTokens(dslParser::ID);
}

tree::TerminalNode* dslParser::Datasheet_propContext::ID(size_t i) {
  return getToken(dslParser::ID, i);
}

tree::TerminalNode* dslParser::Datasheet_propContext::STRING() {
  return getToken(dslParser::STRING, 0);
}


size_t dslParser::Datasheet_propContext::getRuleIndex() const {
  return dslParser::RuleDatasheet_prop;
}

void dslParser::Datasheet_propContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatasheet_prop(this);
}

void dslParser::Datasheet_propContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatasheet_prop(this);
}


antlrcpp::Any dslParser::Datasheet_propContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitDatasheet_prop(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Datasheet_propContext* dslParser::datasheet_prop() {
  Datasheet_propContext *_localctx = _tracker.createInstance<Datasheet_propContext>(_ctx, getState());
  enterRule(_localctx, 40, dslParser::RuleDatasheet_prop);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(286);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case dslParser::T__32: {
        enterOuterAlt(_localctx, 1);
        setState(273);
        match(dslParser::T__32);
        setState(274);
        match(dslParser::T__17);
        setState(275);
        dynamic_cast<Datasheet_propContext *>(_localctx)->extractor = match(dslParser::ID);
        setState(276);
        match(dslParser::T__8);
        setState(277);
        dynamic_cast<Datasheet_propContext *>(_localctx)->title = match(dslParser::STRING);
        setState(278);
        match(dslParser::T__9);
        setState(279);
        match(dslParser::T__33);
        setState(280);
        dynamic_cast<Datasheet_propContext *>(_localctx)->table = match(dslParser::ID);
        setState(281);
        match(dslParser::T__2);
        break;
      }

      case dslParser::T__34: {
        enterOuterAlt(_localctx, 2);
        setState(282);
        match(dslParser::T__34);
        setState(283);
        match(dslParser::T__17);
        setState(284);
        dynamic_cast<Datasheet_propContext *>(_localctx)->filename = match(dslParser::STRING);
        setState(285);
        match(dslParser::T__2);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dim_propContext ------------------------------------------------------------------

dslParser::Dim_propContext::Dim_propContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

dslParser::ExprContext* dslParser::Dim_propContext::expr() {
  return getRuleContext<dslParser::ExprContext>(0);
}


size_t dslParser::Dim_propContext::getRuleIndex() const {
  return dslParser::RuleDim_prop;
}

void dslParser::Dim_propContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDim_prop(this);
}

void dslParser::Dim_propContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDim_prop(this);
}


antlrcpp::Any dslParser::Dim_propContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitDim_prop(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Dim_propContext* dslParser::dim_prop() {
  Dim_propContext *_localctx = _tracker.createInstance<Dim_propContext>(_ctx, getState());
  enterRule(_localctx, 42, dslParser::RuleDim_prop);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(303);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case dslParser::T__35: {
        enterOuterAlt(_localctx, 1);
        setState(288);
        match(dslParser::T__35);
        setState(289);
        match(dslParser::T__17);
        setState(290);
        dynamic_cast<Dim_propContext *>(_localctx)->width = expr();
        setState(291);
        match(dslParser::T__2);
        break;
      }

      case dslParser::T__36: {
        enterOuterAlt(_localctx, 2);
        setState(293);
        match(dslParser::T__36);
        setState(294);
        match(dslParser::T__17);
        setState(295);
        dynamic_cast<Dim_propContext *>(_localctx)->height = expr();
        setState(296);
        match(dslParser::T__2);
        break;
      }

      case dslParser::T__37: {
        enterOuterAlt(_localctx, 3);
        setState(298);
        match(dslParser::T__37);
        setState(299);
        match(dslParser::T__17);
        setState(300);
        dynamic_cast<Dim_propContext *>(_localctx)->layers = expr();
        setState(301);
        match(dslParser::T__2);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryContext ------------------------------------------------------------------

dslParser::PrimaryContext::PrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

dslParser::UnitContext* dslParser::PrimaryContext::unit() {
  return getRuleContext<dslParser::UnitContext>(0);
}

tree::TerminalNode* dslParser::PrimaryContext::NUMBER() {
  return getToken(dslParser::NUMBER, 0);
}

dslParser::ExprContext* dslParser::PrimaryContext::expr() {
  return getRuleContext<dslParser::ExprContext>(0);
}

dslParser::AccessContext* dslParser::PrimaryContext::access() {
  return getRuleContext<dslParser::AccessContext>(0);
}

tree::TerminalNode* dslParser::PrimaryContext::ID() {
  return getToken(dslParser::ID, 0);
}

dslParser::LenContext* dslParser::PrimaryContext::len() {
  return getRuleContext<dslParser::LenContext>(0);
}


size_t dslParser::PrimaryContext::getRuleIndex() const {
  return dslParser::RulePrimary;
}

void dslParser::PrimaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimary(this);
}

void dslParser::PrimaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimary(this);
}


antlrcpp::Any dslParser::PrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitPrimary(this);
  else
    return visitor->visitChildren(this);
}

dslParser::PrimaryContext* dslParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 44, dslParser::RulePrimary);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(315);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case dslParser::NUMBER: {
        enterOuterAlt(_localctx, 1);
        setState(305);
        dynamic_cast<PrimaryContext *>(_localctx)->n = match(dslParser::NUMBER);
        setState(306);
        unit();
        break;
      }

      case dslParser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(307);
        match(dslParser::T__8);
        setState(308);
        expr();
        setState(309);
        match(dslParser::T__9);
        break;
      }

      case dslParser::ID: {
        enterOuterAlt(_localctx, 3);
        setState(311);
        access();
        break;
      }

      case dslParser::T__38: {
        enterOuterAlt(_localctx, 4);
        setState(312);
        dynamic_cast<PrimaryContext *>(_localctx)->length = match(dslParser::T__38);
        setState(313);
        match(dslParser::ID);
        break;
      }

      case dslParser::T__39: {
        enterOuterAlt(_localctx, 5);
        setState(314);
        len();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LenContext ------------------------------------------------------------------

dslParser::LenContext::LenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<dslParser::AccessContext *> dslParser::LenContext::access() {
  return getRuleContexts<dslParser::AccessContext>();
}

dslParser::AccessContext* dslParser::LenContext::access(size_t i) {
  return getRuleContext<dslParser::AccessContext>(i);
}


size_t dslParser::LenContext::getRuleIndex() const {
  return dslParser::RuleLen;
}

void dslParser::LenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLen(this);
}

void dslParser::LenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLen(this);
}


antlrcpp::Any dslParser::LenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitLen(this);
  else
    return visitor->visitChildren(this);
}

dslParser::LenContext* dslParser::len() {
  LenContext *_localctx = _tracker.createInstance<LenContext>(_ctx, getState());
  enterRule(_localctx, 46, dslParser::RuleLen);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(317);
    match(dslParser::T__39);
    setState(318);
    match(dslParser::T__8);
    setState(319);
    access();
    setState(320);
    match(dslParser::T__16);
    setState(321);
    access();
    setState(322);
    match(dslParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

dslParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<dslParser::PrimaryContext *> dslParser::ExprContext::primary() {
  return getRuleContexts<dslParser::PrimaryContext>();
}

dslParser::PrimaryContext* dslParser::ExprContext::primary(size_t i) {
  return getRuleContext<dslParser::PrimaryContext>(i);
}

dslParser::OpContext* dslParser::ExprContext::op() {
  return getRuleContext<dslParser::OpContext>(0);
}


size_t dslParser::ExprContext::getRuleIndex() const {
  return dslParser::RuleExpr;
}

void dslParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void dslParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


antlrcpp::Any dslParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

dslParser::ExprContext* dslParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 48, dslParser::RuleExpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(324);
    primary();
    setState(328);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << dslParser::T__40)
      | (1ULL << dslParser::T__41)
      | (1ULL << dslParser::T__42)
      | (1ULL << dslParser::T__43)
      | (1ULL << dslParser::T__44)
      | (1ULL << dslParser::T__45)
      | (1ULL << dslParser::T__46)
      | (1ULL << dslParser::T__47)
      | (1ULL << dslParser::T__48)
      | (1ULL << dslParser::T__49))) != 0)) {
      setState(325);
      op();
      setState(326);
      primary();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OpContext ------------------------------------------------------------------

dslParser::OpContext::OpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t dslParser::OpContext::getRuleIndex() const {
  return dslParser::RuleOp;
}

void dslParser::OpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOp(this);
}

void dslParser::OpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOp(this);
}


antlrcpp::Any dslParser::OpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitOp(this);
  else
    return visitor->visitChildren(this);
}

dslParser::OpContext* dslParser::op() {
  OpContext *_localctx = _tracker.createInstance<OpContext>(_ctx, getState());
  enterRule(_localctx, 50, dslParser::RuleOp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(340);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case dslParser::T__40: {
        enterOuterAlt(_localctx, 1);
        setState(330);
        dynamic_cast<OpContext *>(_localctx)->operand = match(dslParser::T__40);
        break;
      }

      case dslParser::T__41: {
        enterOuterAlt(_localctx, 2);
        setState(331);
        dynamic_cast<OpContext *>(_localctx)->operand = match(dslParser::T__41);
        break;
      }

      case dslParser::T__42: {
        enterOuterAlt(_localctx, 3);
        setState(332);
        dynamic_cast<OpContext *>(_localctx)->operand = match(dslParser::T__42);
        break;
      }

      case dslParser::T__43: {
        enterOuterAlt(_localctx, 4);
        setState(333);
        dynamic_cast<OpContext *>(_localctx)->operand = match(dslParser::T__43);
        break;
      }

      case dslParser::T__44: {
        enterOuterAlt(_localctx, 5);
        setState(334);
        dynamic_cast<OpContext *>(_localctx)->operand = match(dslParser::T__44);
        break;
      }

      case dslParser::T__45: {
        enterOuterAlt(_localctx, 6);
        setState(335);
        dynamic_cast<OpContext *>(_localctx)->operand = match(dslParser::T__45);
        break;
      }

      case dslParser::T__46: {
        enterOuterAlt(_localctx, 7);
        setState(336);
        dynamic_cast<OpContext *>(_localctx)->operand = match(dslParser::T__46);
        break;
      }

      case dslParser::T__47: {
        enterOuterAlt(_localctx, 8);
        setState(337);
        dynamic_cast<OpContext *>(_localctx)->operand = match(dslParser::T__47);
        break;
      }

      case dslParser::T__48: {
        enterOuterAlt(_localctx, 9);
        setState(338);
        dynamic_cast<OpContext *>(_localctx)->operand = match(dslParser::T__48);
        break;
      }

      case dslParser::T__49: {
        enterOuterAlt(_localctx, 10);
        setState(339);
        dynamic_cast<OpContext *>(_localctx)->operand = match(dslParser::T__49);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AccessContext ------------------------------------------------------------------

dslParser::AccessContext::AccessContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* dslParser::AccessContext::ID() {
  return getToken(dslParser::ID, 0);
}

dslParser::IndexContext* dslParser::AccessContext::index() {
  return getRuleContext<dslParser::IndexContext>(0);
}

std::vector<dslParser::Access_suffixContext *> dslParser::AccessContext::access_suffix() {
  return getRuleContexts<dslParser::Access_suffixContext>();
}

dslParser::Access_suffixContext* dslParser::AccessContext::access_suffix(size_t i) {
  return getRuleContext<dslParser::Access_suffixContext>(i);
}


size_t dslParser::AccessContext::getRuleIndex() const {
  return dslParser::RuleAccess;
}

void dslParser::AccessContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAccess(this);
}

void dslParser::AccessContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAccess(this);
}


antlrcpp::Any dslParser::AccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitAccess(this);
  else
    return visitor->visitChildren(this);
}

dslParser::AccessContext* dslParser::access() {
  AccessContext *_localctx = _tracker.createInstance<AccessContext>(_ctx, getState());
  enterRule(_localctx, 52, dslParser::RuleAccess);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(342);
    match(dslParser::ID);
    setState(344);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == dslParser::T__13) {
      setState(343);
      index();
    }
    setState(349);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == dslParser::T__50) {
      setState(346);
      access_suffix();
      setState(351);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Access_suffixContext ------------------------------------------------------------------

dslParser::Access_suffixContext::Access_suffixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* dslParser::Access_suffixContext::ID() {
  return getToken(dslParser::ID, 0);
}

dslParser::IndexContext* dslParser::Access_suffixContext::index() {
  return getRuleContext<dslParser::IndexContext>(0);
}


size_t dslParser::Access_suffixContext::getRuleIndex() const {
  return dslParser::RuleAccess_suffix;
}

void dslParser::Access_suffixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAccess_suffix(this);
}

void dslParser::Access_suffixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAccess_suffix(this);
}


antlrcpp::Any dslParser::Access_suffixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitAccess_suffix(this);
  else
    return visitor->visitChildren(this);
}

dslParser::Access_suffixContext* dslParser::access_suffix() {
  Access_suffixContext *_localctx = _tracker.createInstance<Access_suffixContext>(_ctx, getState());
  enterRule(_localctx, 54, dslParser::RuleAccess_suffix);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    match(dslParser::T__50);
    setState(353);
    match(dslParser::ID);
    setState(355);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == dslParser::T__13) {
      setState(354);
      index();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IndexContext ------------------------------------------------------------------

dslParser::IndexContext::IndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* dslParser::IndexContext::ID() {
  return getToken(dslParser::ID, 0);
}


size_t dslParser::IndexContext::getRuleIndex() const {
  return dslParser::RuleIndex;
}

void dslParser::IndexContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIndex(this);
}

void dslParser::IndexContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIndex(this);
}


antlrcpp::Any dslParser::IndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitIndex(this);
  else
    return visitor->visitChildren(this);
}

dslParser::IndexContext* dslParser::index() {
  IndexContext *_localctx = _tracker.createInstance<IndexContext>(_ctx, getState());
  enterRule(_localctx, 56, dslParser::RuleIndex);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(357);
    match(dslParser::T__13);
    setState(358);
    match(dslParser::ID);
    setState(359);
    match(dslParser::T__14);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnitContext ------------------------------------------------------------------

dslParser::UnitContext::UnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t dslParser::UnitContext::getRuleIndex() const {
  return dslParser::RuleUnit;
}

void dslParser::UnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnit(this);
}

void dslParser::UnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<dslListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnit(this);
}


antlrcpp::Any dslParser::UnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dslVisitor*>(visitor))
    return parserVisitor->visitUnit(this);
  else
    return visitor->visitChildren(this);
}

dslParser::UnitContext* dslParser::unit() {
  UnitContext *_localctx = _tracker.createInstance<UnitContext>(_ctx, getState());
  enterRule(_localctx, 58, dslParser::RuleUnit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(367);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case dslParser::T__51: {
        enterOuterAlt(_localctx, 1);
        setState(361);
        dynamic_cast<UnitContext *>(_localctx)->name = match(dslParser::T__51);
        break;
      }

      case dslParser::T__52: {
        enterOuterAlt(_localctx, 2);
        setState(362);
        dynamic_cast<UnitContext *>(_localctx)->name = match(dslParser::T__52);
        break;
      }

      case dslParser::T__30: {
        enterOuterAlt(_localctx, 3);
        setState(363);
        dynamic_cast<UnitContext *>(_localctx)->name = match(dslParser::T__30);
        break;
      }

      case dslParser::T__53: {
        enterOuterAlt(_localctx, 4);
        setState(364);
        dynamic_cast<UnitContext *>(_localctx)->name = match(dslParser::T__53);
        break;
      }

      case dslParser::T__54: {
        enterOuterAlt(_localctx, 5);
        setState(365);
        dynamic_cast<UnitContext *>(_localctx)->name = match(dslParser::T__54);
        break;
      }

      case dslParser::T__55: {
        enterOuterAlt(_localctx, 6);
        setState(366);
        dynamic_cast<UnitContext *>(_localctx)->name = match(dslParser::T__55);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> dslParser::_decisionToDFA;
atn::PredictionContextCache dslParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN dslParser::_atn;
std::vector<uint16_t> dslParser::_serializedATN;

std::vector<std::string> dslParser::_ruleNames = {
  "startRule", "directive", "constant", "strategy", "strategy_property", 
  "strategy_foreach", "strategy_call", "constraint", "constraint_property", 
  "constraint_foreach", "constraint_if", "constraint_require", "network", 
  "connection", "object_name", "component", "component_property", "pin_name", 
  "pin_prop", "location_prop", "datasheet_prop", "dim_prop", "primary", 
  "len", "expr", "op", "access", "access_suffix", "index", "unit"
};

std::vector<std::string> dslParser::_literalNames = {
  "", "'const'", "'='", "';'", "'strategy'", "'{'", "'}'", "'for'", "'in'", 
  "'('", "')'", "'constraint'", "'if'", "'require'", "'['", "']'", "'network'", 
  "'->'", "':'", "'component'", "'dimensions'", "'datasheet'", "'pin'", 
  "'value'", "'type'", "','", "'input'", "'output'", "'digital_ground'", 
  "'analog_ground'", "'at'", "'layer'", "'rotatable'", "'extract'", "'as'", 
  "'file'", "'width'", "'height'", "'layers'", "'#'", "'len'", "'=='", "'!= '", 
  "'<'", "'>'", "'<='", "'>='", "'+'", "'-'", "'*'", "'/'", "'.'", "'cm'", 
  "'mm'", "'ohm'", "'uF'", "'integer'"
};

std::vector<std::string> dslParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "STRING", "ID", "NUMBER", "WS", "COMMENT", "LINE_COMMENT"
};

dfa::Vocabulary dslParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> dslParser::_tokenNames;

dslParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x40, 0x174, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x3, 0x2, 0x7, 0x2, 0x40, 0xa, 0x2, 0xc, 0x2, 0xe, 
    0x2, 0x43, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x4c, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x7, 0x5, 0x58, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x5b, 0xb, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x61, 0xa, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x69, 0xa, 
    0x7, 0xc, 0x7, 0xe, 0x7, 0x6c, 0xb, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x7, 0x9, 0x79, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x7c, 0xb, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x83, 0xa, 
    0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 
    0xb, 0x8b, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x8e, 0xb, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x96, 0xa, 0xc, 
    0xc, 0xc, 0xe, 0xc, 0x99, 0xb, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0xa8, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 
    0xab, 0xb, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x6, 
    0xf, 0xb2, 0xa, 0xf, 0xd, 0xf, 0xe, 0xf, 0xb3, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 
    0xbe, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x7, 0x11, 
    0xc4, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 0xc7, 0xb, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x7, 0x12, 0xce, 0xa, 0x12, 0xc, 
    0x12, 0xe, 0x12, 0xd1, 0xb, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x7, 0x12, 0xd7, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0xda, 0xb, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x7, 
    0x12, 0xe2, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0xe5, 0xb, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0xf2, 0xa, 0x12, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0xf7, 0xa, 0x13, 0xc, 0x13, 0xe, 
    0x13, 0xfa, 0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 
    0x14, 0x100, 0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0x10b, 
    0xa, 0x15, 0x5, 0x15, 0x10d, 0xa, 0x15, 0x3, 0x15, 0x5, 0x15, 0x110, 
    0xa, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 
    0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0x121, 0xa, 0x16, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x5, 0x17, 0x132, 0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x5, 0x18, 0x13e, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 
    0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x14b, 0xa, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x157, 0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 
    0x5, 0x1c, 0x15b, 0xa, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 0x15e, 0xa, 0x1c, 
    0xc, 0x1c, 0xe, 0x1c, 0x161, 0xb, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x5, 0x1d, 0x166, 0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x5, 
    0x1f, 0x172, 0xa, 0x1f, 0x3, 0x1f, 0x2, 0x2, 0x20, 0x2, 0x4, 0x6, 0x8, 
    0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 
    0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 
    0x3a, 0x3c, 0x2, 0x2, 0x2, 0x18e, 0x2, 0x41, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x4b, 0x3, 0x2, 0x2, 0x2, 0x6, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x8, 0x53, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x60, 0x3, 0x2, 0x2, 0x2, 0xc, 0x62, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x10, 0x74, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x82, 0x3, 0x2, 0x2, 0x2, 0x14, 0x84, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x91, 0x3, 0x2, 0x2, 0x2, 0x18, 0x9c, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0xa3, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xae, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xb7, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0xbf, 0x3, 0x2, 0x2, 0x2, 0x22, 0xf1, 0x3, 
    0x2, 0x2, 0x2, 0x24, 0xf3, 0x3, 0x2, 0x2, 0x2, 0x26, 0xff, 0x3, 0x2, 
    0x2, 0x2, 0x28, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x120, 0x3, 0x2, 0x2, 
    0x2, 0x2c, 0x131, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x13d, 0x3, 0x2, 0x2, 0x2, 
    0x30, 0x13f, 0x3, 0x2, 0x2, 0x2, 0x32, 0x146, 0x3, 0x2, 0x2, 0x2, 0x34, 
    0x156, 0x3, 0x2, 0x2, 0x2, 0x36, 0x158, 0x3, 0x2, 0x2, 0x2, 0x38, 0x162, 
    0x3, 0x2, 0x2, 0x2, 0x3a, 0x167, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x171, 0x3, 
    0x2, 0x2, 0x2, 0x3e, 0x40, 0x5, 0x4, 0x3, 0x2, 0x3f, 0x3e, 0x3, 0x2, 
    0x2, 0x2, 0x40, 0x43, 0x3, 0x2, 0x2, 0x2, 0x41, 0x3f, 0x3, 0x2, 0x2, 
    0x2, 0x41, 0x42, 0x3, 0x2, 0x2, 0x2, 0x42, 0x44, 0x3, 0x2, 0x2, 0x2, 
    0x43, 0x41, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 0x7, 0x2, 0x2, 0x3, 0x45, 
    0x3, 0x3, 0x2, 0x2, 0x2, 0x46, 0x4c, 0x5, 0x20, 0x11, 0x2, 0x47, 0x4c, 
    0x5, 0x1a, 0xe, 0x2, 0x48, 0x4c, 0x5, 0x10, 0x9, 0x2, 0x49, 0x4c, 0x5, 
    0x8, 0x5, 0x2, 0x4a, 0x4c, 0x5, 0x6, 0x4, 0x2, 0x4b, 0x46, 0x3, 0x2, 
    0x2, 0x2, 0x4b, 0x47, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x48, 0x3, 0x2, 0x2, 
    0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4a, 0x3, 0x2, 0x2, 0x2, 
    0x4c, 0x5, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x7, 0x3, 0x2, 0x2, 0x4e, 
    0x4f, 0x7, 0x3c, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x4, 0x2, 0x2, 0x50, 0x51, 
    0x5, 0x32, 0x1a, 0x2, 0x51, 0x52, 0x7, 0x5, 0x2, 0x2, 0x52, 0x7, 0x3, 
    0x2, 0x2, 0x2, 0x53, 0x54, 0x7, 0x6, 0x2, 0x2, 0x54, 0x55, 0x7, 0x3c, 
    0x2, 0x2, 0x55, 0x59, 0x7, 0x7, 0x2, 0x2, 0x56, 0x58, 0x5, 0xa, 0x6, 
    0x2, 0x57, 0x56, 0x3, 0x2, 0x2, 0x2, 0x58, 0x5b, 0x3, 0x2, 0x2, 0x2, 
    0x59, 0x57, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5a, 
    0x5c, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 
    0x7, 0x8, 0x2, 0x2, 0x5d, 0x9, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x61, 0x5, 
    0xc, 0x7, 0x2, 0x5f, 0x61, 0x5, 0xe, 0x8, 0x2, 0x60, 0x5e, 0x3, 0x2, 
    0x2, 0x2, 0x60, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x61, 0xb, 0x3, 0x2, 0x2, 
    0x2, 0x62, 0x63, 0x7, 0x9, 0x2, 0x2, 0x63, 0x64, 0x7, 0x3c, 0x2, 0x2, 
    0x64, 0x65, 0x7, 0xa, 0x2, 0x2, 0x65, 0x66, 0x5, 0x32, 0x1a, 0x2, 0x66, 
    0x6a, 0x7, 0x7, 0x2, 0x2, 0x67, 0x69, 0x5, 0xa, 0x6, 0x2, 0x68, 0x67, 
    0x3, 0x2, 0x2, 0x2, 0x69, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x68, 0x3, 
    0x2, 0x2, 0x2, 0x6a, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6d, 0x3, 0x2, 
    0x2, 0x2, 0x6c, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x7, 0x8, 0x2, 
    0x2, 0x6e, 0xd, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x5, 0x36, 0x1c, 0x2, 
    0x70, 0x71, 0x7, 0xb, 0x2, 0x2, 0x71, 0x72, 0x7, 0xc, 0x2, 0x2, 0x72, 
    0x73, 0x7, 0x5, 0x2, 0x2, 0x73, 0xf, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 
    0x7, 0xd, 0x2, 0x2, 0x75, 0x76, 0x7, 0x3c, 0x2, 0x2, 0x76, 0x7a, 0x7, 
    0x7, 0x2, 0x2, 0x77, 0x79, 0x5, 0x12, 0xa, 0x2, 0x78, 0x77, 0x3, 0x2, 
    0x2, 0x2, 0x79, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x78, 0x3, 0x2, 0x2, 
    0x2, 0x7a, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7d, 0x3, 0x2, 0x2, 0x2, 
    0x7c, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7e, 0x7, 0x8, 0x2, 0x2, 0x7e, 
    0x11, 0x3, 0x2, 0x2, 0x2, 0x7f, 0x83, 0x5, 0x14, 0xb, 0x2, 0x80, 0x83, 
    0x5, 0x18, 0xd, 0x2, 0x81, 0x83, 0x5, 0x16, 0xc, 0x2, 0x82, 0x7f, 0x3, 
    0x2, 0x2, 0x2, 0x82, 0x80, 0x3, 0x2, 0x2, 0x2, 0x82, 0x81, 0x3, 0x2, 
    0x2, 0x2, 0x83, 0x13, 0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x7, 0x9, 0x2, 
    0x2, 0x85, 0x86, 0x7, 0x3c, 0x2, 0x2, 0x86, 0x87, 0x7, 0xa, 0x2, 0x2, 
    0x87, 0x88, 0x5, 0x32, 0x1a, 0x2, 0x88, 0x8c, 0x7, 0x7, 0x2, 0x2, 0x89, 
    0x8b, 0x5, 0x12, 0xa, 0x2, 0x8a, 0x89, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x8e, 
    0x3, 0x2, 0x2, 0x2, 0x8c, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 0x3, 
    0x2, 0x2, 0x2, 0x8d, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8c, 0x3, 0x2, 
    0x2, 0x2, 0x8f, 0x90, 0x7, 0x8, 0x2, 0x2, 0x90, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0x91, 0x92, 0x7, 0xe, 0x2, 0x2, 0x92, 0x93, 0x5, 0x32, 0x1a, 0x2, 
    0x93, 0x97, 0x7, 0x7, 0x2, 0x2, 0x94, 0x96, 0x5, 0x12, 0xa, 0x2, 0x95, 
    0x94, 0x3, 0x2, 0x2, 0x2, 0x96, 0x99, 0x3, 0x2, 0x2, 0x2, 0x97, 0x95, 
    0x3, 0x2, 0x2, 0x2, 0x97, 0x98, 0x3, 0x2, 0x2, 0x2, 0x98, 0x9a, 0x3, 
    0x2, 0x2, 0x2, 0x99, 0x97, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x7, 0x8, 
    0x2, 0x2, 0x9b, 0x17, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x7, 0xf, 0x2, 
    0x2, 0x9d, 0x9e, 0x7, 0x10, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0x3d, 0x2, 0x2, 
    0x9f, 0xa0, 0x7, 0x11, 0x2, 0x2, 0xa0, 0xa1, 0x5, 0x32, 0x1a, 0x2, 0xa1, 
    0xa2, 0x7, 0x5, 0x2, 0x2, 0xa2, 0x19, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa4, 
    0x7, 0x12, 0x2, 0x2, 0xa4, 0xa5, 0x5, 0x1e, 0x10, 0x2, 0xa5, 0xa9, 0x7, 
    0x7, 0x2, 0x2, 0xa6, 0xa8, 0x5, 0x1c, 0xf, 0x2, 0xa7, 0xa6, 0x3, 0x2, 
    0x2, 0x2, 0xa8, 0xab, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xa7, 0x3, 0x2, 0x2, 
    0x2, 0xa9, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xac, 0x3, 0x2, 0x2, 0x2, 
    0xab, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xac, 0xad, 0x7, 0x8, 0x2, 0x2, 0xad, 
    0x1b, 0x3, 0x2, 0x2, 0x2, 0xae, 0xb1, 0x5, 0x36, 0x1c, 0x2, 0xaf, 0xb0, 
    0x7, 0x13, 0x2, 0x2, 0xb0, 0xb2, 0x5, 0x36, 0x1c, 0x2, 0xb1, 0xaf, 0x3, 
    0x2, 0x2, 0x2, 0xb2, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb1, 0x3, 0x2, 
    0x2, 0x2, 0xb3, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xb5, 0x3, 0x2, 0x2, 
    0x2, 0xb5, 0xb6, 0x7, 0x5, 0x2, 0x2, 0xb6, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0xb7, 0xbd, 0x7, 0x3c, 0x2, 0x2, 0xb8, 0xb9, 0x7, 0x10, 0x2, 0x2, 0xb9, 
    0xba, 0x7, 0x3c, 0x2, 0x2, 0xba, 0xbb, 0x7, 0x14, 0x2, 0x2, 0xbb, 0xbc, 
    0x7, 0x3c, 0x2, 0x2, 0xbc, 0xbe, 0x7, 0x11, 0x2, 0x2, 0xbd, 0xb8, 0x3, 
    0x2, 0x2, 0x2, 0xbd, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xbe, 0x1f, 0x3, 0x2, 
    0x2, 0x2, 0xbf, 0xc0, 0x7, 0x15, 0x2, 0x2, 0xc0, 0xc1, 0x5, 0x1e, 0x10, 
    0x2, 0xc1, 0xc5, 0x7, 0x7, 0x2, 0x2, 0xc2, 0xc4, 0x5, 0x22, 0x12, 0x2, 
    0xc3, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xc5, 
    0xc3, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc8, 
    0x3, 0x2, 0x2, 0x2, 0xc7, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xc9, 0x7, 
    0x8, 0x2, 0x2, 0xc9, 0x21, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcb, 0x7, 0x16, 
    0x2, 0x2, 0xcb, 0xcf, 0x7, 0x7, 0x2, 0x2, 0xcc, 0xce, 0x5, 0x2c, 0x17, 
    0x2, 0xcd, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xce, 0xd1, 0x3, 0x2, 0x2, 0x2, 
    0xcf, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xd0, 0x3, 0x2, 0x2, 0x2, 0xd0, 
    0xd2, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xf2, 
    0x7, 0x8, 0x2, 0x2, 0xd3, 0xd4, 0x7, 0x17, 0x2, 0x2, 0xd4, 0xd8, 0x7, 
    0x7, 0x2, 0x2, 0xd5, 0xd7, 0x5, 0x2a, 0x16, 0x2, 0xd6, 0xd5, 0x3, 0x2, 
    0x2, 0x2, 0xd7, 0xda, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xd6, 0x3, 0x2, 0x2, 
    0x2, 0xd8, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xdb, 0x3, 0x2, 0x2, 0x2, 
    0xda, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xf2, 0x7, 0x8, 0x2, 0x2, 0xdc, 
    0xf2, 0x5, 0x28, 0x15, 0x2, 0xdd, 0xde, 0x7, 0x18, 0x2, 0x2, 0xde, 0xdf, 
    0x5, 0x24, 0x13, 0x2, 0xdf, 0xe3, 0x7, 0x7, 0x2, 0x2, 0xe0, 0xe2, 0x5, 
    0x26, 0x14, 0x2, 0xe1, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe5, 0x3, 0x2, 
    0x2, 0x2, 0xe3, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe4, 0x3, 0x2, 0x2, 
    0x2, 0xe4, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe3, 0x3, 0x2, 0x2, 0x2, 
    0xe6, 0xe7, 0x7, 0x8, 0x2, 0x2, 0xe7, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xe8, 
    0xe9, 0x7, 0x19, 0x2, 0x2, 0xe9, 0xea, 0x7, 0x14, 0x2, 0x2, 0xea, 0xeb, 
    0x5, 0x32, 0x1a, 0x2, 0xeb, 0xec, 0x7, 0x5, 0x2, 0x2, 0xec, 0xf2, 0x3, 
    0x2, 0x2, 0x2, 0xed, 0xee, 0x7, 0x1a, 0x2, 0x2, 0xee, 0xef, 0x7, 0x14, 
    0x2, 0x2, 0xef, 0xf0, 0x7, 0x3b, 0x2, 0x2, 0xf0, 0xf2, 0x7, 0x5, 0x2, 
    0x2, 0xf1, 0xca, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xd3, 0x3, 0x2, 0x2, 0x2, 
    0xf1, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xdd, 0x3, 0x2, 0x2, 0x2, 0xf1, 
    0xe8, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xed, 0x3, 0x2, 0x2, 0x2, 0xf2, 0x23, 
    0x3, 0x2, 0x2, 0x2, 0xf3, 0xf8, 0x7, 0x3c, 0x2, 0x2, 0xf4, 0xf5, 0x7, 
    0x1b, 0x2, 0x2, 0xf5, 0xf7, 0x7, 0x3c, 0x2, 0x2, 0xf6, 0xf4, 0x3, 0x2, 
    0x2, 0x2, 0xf7, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xf6, 0x3, 0x2, 0x2, 
    0x2, 0xf8, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xf9, 0x25, 0x3, 0x2, 0x2, 0x2, 
    0xfa, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xfb, 0x100, 0x7, 0x1c, 0x2, 0x2, 0xfc, 
    0x100, 0x7, 0x1d, 0x2, 0x2, 0xfd, 0x100, 0x7, 0x1e, 0x2, 0x2, 0xfe, 
    0x100, 0x7, 0x1f, 0x2, 0x2, 0xff, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfc, 
    0x3, 0x2, 0x2, 0x2, 0xff, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfe, 0x3, 
    0x2, 0x2, 0x2, 0x100, 0x101, 0x3, 0x2, 0x2, 0x2, 0x101, 0x102, 0x7, 
    0x5, 0x2, 0x2, 0x102, 0x27, 0x3, 0x2, 0x2, 0x2, 0x103, 0x104, 0x7, 0x20, 
    0x2, 0x2, 0x104, 0x105, 0x7, 0x14, 0x2, 0x2, 0x105, 0x106, 0x5, 0x32, 
    0x1a, 0x2, 0x106, 0x107, 0x7, 0x1b, 0x2, 0x2, 0x107, 0x10a, 0x5, 0x32, 
    0x1a, 0x2, 0x108, 0x109, 0x7, 0x21, 0x2, 0x2, 0x109, 0x10b, 0x7, 0x3d, 
    0x2, 0x2, 0x10a, 0x108, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x10b, 0x3, 0x2, 
    0x2, 0x2, 0x10b, 0x10d, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x103, 0x3, 0x2, 
    0x2, 0x2, 0x10c, 0x10d, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10f, 0x3, 0x2, 
    0x2, 0x2, 0x10e, 0x110, 0x7, 0x22, 0x2, 0x2, 0x10f, 0x10e, 0x3, 0x2, 
    0x2, 0x2, 0x10f, 0x110, 0x3, 0x2, 0x2, 0x2, 0x110, 0x111, 0x3, 0x2, 
    0x2, 0x2, 0x111, 0x112, 0x7, 0x5, 0x2, 0x2, 0x112, 0x29, 0x3, 0x2, 0x2, 
    0x2, 0x113, 0x114, 0x7, 0x23, 0x2, 0x2, 0x114, 0x115, 0x7, 0x14, 0x2, 
    0x2, 0x115, 0x116, 0x7, 0x3c, 0x2, 0x2, 0x116, 0x117, 0x7, 0xb, 0x2, 
    0x2, 0x117, 0x118, 0x7, 0x3b, 0x2, 0x2, 0x118, 0x119, 0x7, 0xc, 0x2, 
    0x2, 0x119, 0x11a, 0x7, 0x24, 0x2, 0x2, 0x11a, 0x11b, 0x7, 0x3c, 0x2, 
    0x2, 0x11b, 0x121, 0x7, 0x5, 0x2, 0x2, 0x11c, 0x11d, 0x7, 0x25, 0x2, 
    0x2, 0x11d, 0x11e, 0x7, 0x14, 0x2, 0x2, 0x11e, 0x11f, 0x7, 0x3b, 0x2, 
    0x2, 0x11f, 0x121, 0x7, 0x5, 0x2, 0x2, 0x120, 0x113, 0x3, 0x2, 0x2, 
    0x2, 0x120, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x121, 0x2b, 0x3, 0x2, 0x2, 0x2, 
    0x122, 0x123, 0x7, 0x26, 0x2, 0x2, 0x123, 0x124, 0x7, 0x14, 0x2, 0x2, 
    0x124, 0x125, 0x5, 0x32, 0x1a, 0x2, 0x125, 0x126, 0x7, 0x5, 0x2, 0x2, 
    0x126, 0x132, 0x3, 0x2, 0x2, 0x2, 0x127, 0x128, 0x7, 0x27, 0x2, 0x2, 
    0x128, 0x129, 0x7, 0x14, 0x2, 0x2, 0x129, 0x12a, 0x5, 0x32, 0x1a, 0x2, 
    0x12a, 0x12b, 0x7, 0x5, 0x2, 0x2, 0x12b, 0x132, 0x3, 0x2, 0x2, 0x2, 
    0x12c, 0x12d, 0x7, 0x28, 0x2, 0x2, 0x12d, 0x12e, 0x7, 0x14, 0x2, 0x2, 
    0x12e, 0x12f, 0x5, 0x32, 0x1a, 0x2, 0x12f, 0x130, 0x7, 0x5, 0x2, 0x2, 
    0x130, 0x132, 0x3, 0x2, 0x2, 0x2, 0x131, 0x122, 0x3, 0x2, 0x2, 0x2, 
    0x131, 0x127, 0x3, 0x2, 0x2, 0x2, 0x131, 0x12c, 0x3, 0x2, 0x2, 0x2, 
    0x132, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x133, 0x134, 0x7, 0x3d, 0x2, 0x2, 
    0x134, 0x13e, 0x5, 0x3c, 0x1f, 0x2, 0x135, 0x136, 0x7, 0xb, 0x2, 0x2, 
    0x136, 0x137, 0x5, 0x32, 0x1a, 0x2, 0x137, 0x138, 0x7, 0xc, 0x2, 0x2, 
    0x138, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x139, 0x13e, 0x5, 0x36, 0x1c, 0x2, 
    0x13a, 0x13b, 0x7, 0x29, 0x2, 0x2, 0x13b, 0x13e, 0x7, 0x3c, 0x2, 0x2, 
    0x13c, 0x13e, 0x5, 0x30, 0x19, 0x2, 0x13d, 0x133, 0x3, 0x2, 0x2, 0x2, 
    0x13d, 0x135, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x139, 0x3, 0x2, 0x2, 0x2, 
    0x13d, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x13c, 0x3, 0x2, 0x2, 0x2, 
    0x13e, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x140, 0x7, 0x2a, 0x2, 0x2, 
    0x140, 0x141, 0x7, 0xb, 0x2, 0x2, 0x141, 0x142, 0x5, 0x36, 0x1c, 0x2, 
    0x142, 0x143, 0x7, 0x13, 0x2, 0x2, 0x143, 0x144, 0x5, 0x36, 0x1c, 0x2, 
    0x144, 0x145, 0x7, 0xc, 0x2, 0x2, 0x145, 0x31, 0x3, 0x2, 0x2, 0x2, 0x146, 
    0x14a, 0x5, 0x2e, 0x18, 0x2, 0x147, 0x148, 0x5, 0x34, 0x1b, 0x2, 0x148, 
    0x149, 0x5, 0x2e, 0x18, 0x2, 0x149, 0x14b, 0x3, 0x2, 0x2, 0x2, 0x14a, 
    0x147, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x14b, 0x3, 0x2, 0x2, 0x2, 0x14b, 
    0x33, 0x3, 0x2, 0x2, 0x2, 0x14c, 0x157, 0x7, 0x2b, 0x2, 0x2, 0x14d, 
    0x157, 0x7, 0x2c, 0x2, 0x2, 0x14e, 0x157, 0x7, 0x2d, 0x2, 0x2, 0x14f, 
    0x157, 0x7, 0x2e, 0x2, 0x2, 0x150, 0x157, 0x7, 0x2f, 0x2, 0x2, 0x151, 
    0x157, 0x7, 0x30, 0x2, 0x2, 0x152, 0x157, 0x7, 0x31, 0x2, 0x2, 0x153, 
    0x157, 0x7, 0x32, 0x2, 0x2, 0x154, 0x157, 0x7, 0x33, 0x2, 0x2, 0x155, 
    0x157, 0x7, 0x34, 0x2, 0x2, 0x156, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x156, 
    0x14d, 0x3, 0x2, 0x2, 0x2, 0x156, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x156, 
    0x14f, 0x3, 0x2, 0x2, 0x2, 0x156, 0x150, 0x3, 0x2, 0x2, 0x2, 0x156, 
    0x151, 0x3, 0x2, 0x2, 0x2, 0x156, 0x152, 0x3, 0x2, 0x2, 0x2, 0x156, 
    0x153, 0x3, 0x2, 0x2, 0x2, 0x156, 0x154, 0x3, 0x2, 0x2, 0x2, 0x156, 
    0x155, 0x3, 0x2, 0x2, 0x2, 0x157, 0x35, 0x3, 0x2, 0x2, 0x2, 0x158, 0x15a, 
    0x7, 0x3c, 0x2, 0x2, 0x159, 0x15b, 0x5, 0x3a, 0x1e, 0x2, 0x15a, 0x159, 
    0x3, 0x2, 0x2, 0x2, 0x15a, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x15f, 
    0x3, 0x2, 0x2, 0x2, 0x15c, 0x15e, 0x5, 0x38, 0x1d, 0x2, 0x15d, 0x15c, 
    0x3, 0x2, 0x2, 0x2, 0x15e, 0x161, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x15d, 
    0x3, 0x2, 0x2, 0x2, 0x15f, 0x160, 0x3, 0x2, 0x2, 0x2, 0x160, 0x37, 0x3, 
    0x2, 0x2, 0x2, 0x161, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x162, 0x163, 0x7, 
    0x35, 0x2, 0x2, 0x163, 0x165, 0x7, 0x3c, 0x2, 0x2, 0x164, 0x166, 0x5, 
    0x3a, 0x1e, 0x2, 0x165, 0x164, 0x3, 0x2, 0x2, 0x2, 0x165, 0x166, 0x3, 
    0x2, 0x2, 0x2, 0x166, 0x39, 0x3, 0x2, 0x2, 0x2, 0x167, 0x168, 0x7, 0x10, 
    0x2, 0x2, 0x168, 0x169, 0x7, 0x3c, 0x2, 0x2, 0x169, 0x16a, 0x7, 0x11, 
    0x2, 0x2, 0x16a, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x16b, 0x172, 0x7, 0x36, 
    0x2, 0x2, 0x16c, 0x172, 0x7, 0x37, 0x2, 0x2, 0x16d, 0x172, 0x7, 0x21, 
    0x2, 0x2, 0x16e, 0x172, 0x7, 0x38, 0x2, 0x2, 0x16f, 0x172, 0x7, 0x39, 
    0x2, 0x2, 0x170, 0x172, 0x7, 0x3a, 0x2, 0x2, 0x171, 0x16b, 0x3, 0x2, 
    0x2, 0x2, 0x171, 0x16c, 0x3, 0x2, 0x2, 0x2, 0x171, 0x16d, 0x3, 0x2, 
    0x2, 0x2, 0x171, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x171, 0x16f, 0x3, 0x2, 
    0x2, 0x2, 0x171, 0x170, 0x3, 0x2, 0x2, 0x2, 0x172, 0x3d, 0x3, 0x2, 0x2, 
    0x2, 0x21, 0x41, 0x4b, 0x59, 0x60, 0x6a, 0x7a, 0x82, 0x8c, 0x97, 0xa9, 
    0xb3, 0xbd, 0xc5, 0xcf, 0xd8, 0xe3, 0xf1, 0xf8, 0xff, 0x10a, 0x10c, 
    0x10f, 0x120, 0x131, 0x13d, 0x14a, 0x156, 0x15a, 0x15f, 0x165, 0x171, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

dslParser::Initializer dslParser::_init;
