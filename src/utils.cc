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
