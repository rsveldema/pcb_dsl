#ifndef UTILZ___H__H_
#define UTILZ___H__H_

#include <string>
#include <vector>
#include <sstream>
#include <math.h>

static inline
double radians_to_degrees(double radians)
{
  return (radians / M_PI) * 180.0;
}

static inline
double degrees_to_radians(double degrees)
{
  return (degrees / 180.0) * M_PI;
}

namespace utils
{
  template<typename T>
    void erase(std::vector<T> &vec, T &search)
    {
      for (auto it = vec.begin(); it != vec.end(); it++)
	{
	  T &k = *it;
	  if (k == search)
	    {
	      vec.erase(it);
	      return;
	    }
	}
      fprintf(stderr, "failed to find element\n");
      abort();
    }

  static inline
  const std::string type_to_string(const char *str)
  {
    return str;
  }
  
  
  template<typename T>
    const std::string type_to_string(const std::vector<T*> &v)
    {
      std::ostringstream ss;
      const char *pre = "";
      for (auto k : v)
	{
	  ss << pre;
	  ss << k->getText();
	  pre = ", ";
	}
      return ss.str();
    };
  
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
std::string destringify(const std::string &s);
unsigned get_unique_id();
std::string normalize_text(const std::string &s);
std::string normalize_ident(const std::string &s);
bool file_exists(const std::string &filename);
#endif
