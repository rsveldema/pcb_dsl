#ifndef SCORE____H__
#define SCORE____H__

class score_data_t
{
public:
  static constexpr unsigned MAX_SCORE_DATA = 256;
  
 private:
  unsigned count = 0;
  int32_t values[MAX_SCORE_DATA];
  const char * _descr[MAX_SCORE_DATA];

 public:
  inline int32_t at(unsigned ix) const
  {
    assert(ix < size());
    return values[ix];
  }
  
  inline const char *descr(unsigned ix) const
  {
    assert(ix < size());
    return _descr[ix];
  }
    
  unsigned size() const
  {
    return count;
  }
  
  void add(int32_t v,
	   const char *name)
  {
    assert(count < MAX_SCORE_DATA);
    values[count]  = v;
    _descr[count]  = name;
    count++;
  }
};

class score_t
{
 public:
  static constexpr unsigned PRIO_LEVELS = 2;
  score_data_t values[PRIO_LEVELS];

  bool is_better_than(const score_t &s, unsigned seed, unsigned prio) const;
  bool is_everywhere_better_than(const score_t &s, unsigned seed) const;
  int int_comparer(const score_t &s, unsigned seed, unsigned prio) const;
  std::string str() const;
  
  size_t size(unsigned prio) const
  {
    assert(prio < PRIO_LEVELS);
    return values[prio].size();
  }

  void add(unsigned prio,
	   int32_t v,
	   const char *descr)
  {
    assert(prio < PRIO_LEVELS);
    values[prio].add(v, descr);
  }
};

typedef std::pair<score_t, Model*> compare_t;

#endif
