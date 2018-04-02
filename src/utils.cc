#include "utils.hpp"

#include <boost/algorithm/string/replace.hpp>
#include <chrono>

uint64_t currentTimeMillis()
{
	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto epoch = now_ms.time_since_epoch();

	auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
	long duration = value.count();
	return duration;
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


