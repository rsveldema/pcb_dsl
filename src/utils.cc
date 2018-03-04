#include "utils.h"
#include <sys/time.h>
#include <boost/algorithm/string/replace.hpp>

uint64_t currentTimeMillis()
{
  timeval tv;
  gettimeofday(&tv, NULL);
  return ((uint64_t) tv.tv_sec*1000) + (tv.tv_usec/1000);
}

int randrange(int min, int max) 
{
  return min + (rand() % (max - min));
}

unsigned randrange(unsigned max) 
{
   return rand() % max;
}


bool file_exists(const std::string &filename)
{
  FILE *f = fopen(filename.c_str(), "r");
  if (! f) return false;
  fclose(f);
  return true;
}


std::string destringify(const std::string &s)
{
  return s.substr(1, s.size()-2);
}

unsigned get_unique_id()
{
  static unsigned id;
  return id++;
}

std::string normalize_ident(const std::string &str)
{
  std::string s(str);
  boost::replace_all(s, "-", "_");
  boost::replace_all(s, " ", "_");
  return s;
}

std::string normalize_text(const std::string &str)
{
  std::string s(str);
  boost::replace_all(s, "–", "-");
  return s;
}


