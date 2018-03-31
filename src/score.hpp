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
  score_data_t values;

  bool operator < (const score_t &s) const;
  int int_comparer(const score_t &s) const;

  bool is_better_at(unsigned ix, const score_t &a) const;
  std::string str() const;
  
  size_t size() const
  {
    return values.size();
  }

  void add(int32_t v,
	   const char *descr)
  {
    values.add(v, descr);
  }
};

typedef std::pair<score_t, Model*> compare_t;

#endif
