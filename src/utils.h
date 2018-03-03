#ifndef UTILZ___H__H_
#define UTILZ___H__H_

#include <string>
#include <sstream>


namespace utils
{
  template<typename T>
    const std::string type_to_string(const T &v)
    {
      std::ostringstream ss;
      ss << v;
      return ss.str();
    };
  
  template<typename...P>
    void vtspf_priv(std::string &output)
    {
    }
  
  template<typename H, typename...P>
    void vtspf_priv(std::string &output, H h, P...p)
  {
    output += type_to_string(h);
    vtspf_priv(output, p...);
  }
  
  template<typename...P>
    std::string str(P...p)
    {
      std::string output;
      vtspf_priv(output, p...);
      return output;
    }

  template<typename...P>
  void print(P...p)
  {
    auto s = str(p...);
    printf("%s\n", s.c_str());
  }
}


uint64_t currentTimeMillis();
static inline double currentTimeSecs() { return currentTimeMillis() / 1000.0; }
int randrange(int min, int max);
unsigned randrange(unsigned max);

#endif
