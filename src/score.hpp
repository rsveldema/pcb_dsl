#ifndef SCORE____H__
#define SCORE____H__

class score_data_t
{
 private:
  unsigned count = 0;
  static constexpr unsigned MAX_SCORE_DATA = 128;  
  int32_t values[MAX_SCORE_DATA];

 public:
  int32_t at(unsigned ix) const
  {
    assert(ix < size());
    return values[ix];
  }
    
  unsigned size() const { return count; }
  void push_back(int32_t a)
  {
    assert(count < MAX_SCORE_DATA);
    values[count] = a;
    count++;
  }
};

class score_t
{
 public:
  score_data_t values;

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
