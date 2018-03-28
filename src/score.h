#ifndef SCORE____H__
#define SCORE____H__


struct score_t
{
  size_t   num_comp = 0;
  size_t   num_layers = 0;
  unsigned num_overlaps = 0;
  double   connection_lengths = 0;
  unsigned crossing_lines = 0;
  unsigned sharp_angles = 0;
  unsigned magic = 0;

  static constexpr unsigned MAGIC = 1234;

  bool operator < (const score_t &s) const;
  int int_comparer(const score_t &s) const;   

  std::string str() const;
};


typedef std::pair<score_t, Model*> compare_t;

#endif
