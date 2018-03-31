#ifndef MY_VECTOR__G_H____
#define MY_VECTOR__G_H____


template <typename T, unsigned SIZE>
class fixedsize_vector
{
private:
  T data[SIZE];
  unsigned count = 0;

public:
  void reset(const T &a)
  {
    count = 0;
    push_back(a);
  }

  void set(unsigned ix, const T &to_pin)
  {
    assert(ix < count);
    data[ix] = to_pin;
  }
  
  T &operator[] (unsigned ix)
  {
    assert(ix < count);
    return data[ix];
  }

  const T &operator[] (unsigned ix) const
  {
    assert(ix < count);
    return data[ix];
  }
  
  unsigned size() const
  {
    return count;
  }
  
  void push_back(const T &d)
  {
    assert(count < SIZE);
    data[count++] = d;
  }
};



#endif
