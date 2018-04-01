#ifndef CONSTRAITS__HH__H__
#define CONSTRAITS__HH__H__


class RuleExpr
{
 public:
  enum Type
    {
      NONE,
      DIST,
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

  Point::pos_t dist;
  std::string name;
  RuleExpr *lhs = nullptr;
  RuleExpr *rhs = nullptr;
  unsigned prio = 0;
  
 public:
  RuleExpr(const MillimeterLength &d)
    : dist(Point::getPointLen(d))
    {
      type = DIST;
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

  unsigned get_prio() const
  {
    return prio;
  }
  void set_prio(unsigned p)
  {
    this->prio = p;
  }

  Component *find_component(Model *m);
  Pin *find_pin(Model *m);
  int64_t eval(Model *m);
  score_elt_t score(Model *m);
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
  void add(unsigned prio,
	   RuleExpr *r)
  {
    r->set_prio(prio);
    rules.push_back(r);
  }
  void check(Model *m);
  void score(Model *m, score_t &result);
};


#endif
