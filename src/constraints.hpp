#ifndef CONSTRAITS__HH__H__
#define CONSTRAITS__HH__H__


class RuleExpr
{
 public:
  enum Type
    {
      NONE,
      INT_CONST,
      COMP_ACCESS,
      PIN_ACCESS,
      LEN,
      EQ,
      NEQ,

      ADD,
      SUB,
      MUL,
      DIV
    };

 private:
  Type type = NONE;

  int iconst = 0;
  std::string name;
  RuleExpr *lhs = nullptr;
  RuleExpr *rhs = nullptr;


 public:
  RuleExpr(int c)
    {
      type = INT_CONST;
      iconst = c;
    }

  RuleExpr(const std::string &s)
    : name(s)
    {
      type = COMP_ACCESS;
    }
  
  RuleExpr(RuleExpr *r, const std::string &s)
    : name(s)
    {
      lhs = r;
      type = PIN_ACCESS;
    }
      
  RuleExpr(const std::string &op,
	   RuleExpr *lhs,
	   RuleExpr *rhs);
 RuleExpr(Type t,
	   RuleExpr *lhs,
	   RuleExpr *rhs)
    : type(t)
    {
      this->lhs = lhs;
      this->rhs = rhs;
    }
  void check(Model *m, bool root);
  std::string str() const;

  Component *find_component(Model *m);
  Pin *find_pin(Model *m);
  int64_t eval(Model *m);
  int score(Model *m);
};


class Constraint
{
private:
  std::string name;
  std::vector<RuleExpr *> rules;
public:
  Constraint(const std::string &_name)
    : name(_name)
  {
  }
  void add(RuleExpr *r)
  {
    rules.push_back(r);
  }
  void check(Model *m);
  void score(Model *m, score_data_t &result);
};


#endif
