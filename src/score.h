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

  void add_penalties();
  bool operator < (const score_t &s);

  std::string str() const;
};

#endif
