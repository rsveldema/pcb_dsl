#ifndef SCORE____H__
#define SCORE____H__


struct score_t
{
public:
  std::vector<int32_t> values;

public:
  bool operator < (const score_t &s) const;
  int int_comparer(const score_t &s) const;

  bool is_better_at(unsigned ix, const score_t &a) const;
  std::string str() const;

  size_t size() const
  {
    return values.size();
  }

  void add(int32_t v)
  {
    values.push_back(v);
  }
};


typedef std::pair<score_t, Model*> compare_t;

#endif
