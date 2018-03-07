#include "outline.h"


void test_overlap()
{
  Outline r1, r2;

  r1.addRect(CentimeterPoint(0,0,0),
	     CentimeterPoint(5,5,0));
  
  r2.addRect(CentimeterPoint(3,3,0),
	     CentimeterPoint(8,8,0));

  bool overlap = r1.overlaps(r2);
  printf("overlap = %d\n", overlap);
}



void test_above()
{
  Outline r1, r2;

  r1.addRect(CentimeterPoint(0,0,0),
	     CentimeterPoint(5,5,0));
  
  r2.addRect(CentimeterPoint(8,8,0),
	     CentimeterPoint(18,18,0));

  bool overlap = r1.overlaps(r2);
  printf("above = %d\n", overlap);
}
       


int main(int argc,
	 char **argv)
{
  test_overlap();
  test_above();
  
  return 0;
}
