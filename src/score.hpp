#ifndef SCORE____H__
#define SCORE____H__

/** the order of items in this enum tells which thing 
 * we're going to optimize against first.
 */
enum class Importance
  {
    USER_1,
    USER_2,
    OVERLAP,
    SUM_LENGTHS,
    CROSSING_PINS,
    CROSSING_WIRES,
    SHARP_TURNS,
    NUM_COMPONENTS,
    NUM_LAYERS,
    NONE
  };


struct score_elt_t
{
  typedef int64_t val_t;
    
private:
  
  val_t v;
  val_t max;
  const char *_descr;
  Importance importance;
  
public:
  score_elt_t()
    : v(0), max(0), _descr(0), importance(Importance::NONE)
  {
  }

  score_elt_t(val_t _v,
	      val_t _max,
	      const char *_descr,
	      Importance _importance)
    : v(_v),
      max(_max),
      _descr(_descr),
      importance(_importance)
  {
    assert(v <= max);
    assert(importance != Importance::NONE);
  }

  Importance get_importance() const
  {
    return importance;
  }

  static int qsort_comparer(const void *a,
			    const void *b)
  {
    score_elt_t *e1 = (score_elt_t *)a;
    score_elt_t *e2 = (score_elt_t *)b;
    return (int)e1->importance - (int)e2->importance;
  }
  
  val_t raw() const
  {
    return v;
  }

  val_t raw_max() const
  {
    return max;
  }

  val_t normalized() const
  {
    return (v * (val_t)10000) / max;
  }
  
  void add(const score_elt_t &v)
  {    
    this->v   += v.v;
    this->max += v.max;
    if (this->importance == Importance::NONE)
      {
	this->importance = v.importance;
      }
    _descr = v._descr;
  }
  
  const char *descr() const { return _descr; }
};


template<unsigned LEN>
class template_score_data_t
{
public:
  static constexpr unsigned MAX_SCORE_DATA = LEN;
  
 private:
  unsigned fill = 0;
  unsigned count = 0;
  score_elt_t values[MAX_SCORE_DATA];

 public:
  inline const score_elt_t &at(unsigned ix) const
  {
    assert(ix < size());
    return values[ix];
  }
  
  inline const char *descr(unsigned ix) const
  {
    return at(ix).descr();
  }
    
  unsigned size() const
  {
    return count;
  }
  
  void add(const score_elt_t &v)
  {
    values[fill].add(v);
    fill = (fill + 1) % MAX_SCORE_DATA;
    if (count < LEN)
      {
	count++;
      }
  }
  void sort()
  {
    qsort(values, size(), sizeof(values[0]),
	  score_elt_t::qsort_comparer);
  }
};


typedef template_score_data_t<16>   length_score_t;
typedef template_score_data_t<256> score_data_t;


class score_t
{
 public:  
  score_data_t values;

  bool is_better_than(score_t &s);
  int int_comparer(score_t &s);
  
  std::string str() const;
  
  size_t size() const
  {
    return values.size();
  }

  void add(length_score_t &s)
  {
    for (unsigned i = 0; i < s.size(); i++)
      {
	add(s.at(i));
      }
  }

  void add(score_elt_t v)
  {
    values.add(v);
  }
  
  void sort()
  {
    values.sort();
  }
};

typedef std::pair<score_t, Model*> compare_t;

#endif
