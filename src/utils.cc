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
  /*
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
  */
   return min + (rand() % (( max + 1 ) - min));
}

unsigned randrange(unsigned max) 
{
  /*
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
  */
   return rand() % max;
}
