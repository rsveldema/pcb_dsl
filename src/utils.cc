#include "utils.h"
#include <sys/time.h>

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

