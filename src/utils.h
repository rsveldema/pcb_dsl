#ifndef UTILZ___H__H_
#define UTILZ___H__H_

#include <string>
#include <vector>
#include <sstream>


namespace utils
{
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
bool valid_pin_name(const std::string &s);
bool file_exists(const std::string &filename);
#endif
