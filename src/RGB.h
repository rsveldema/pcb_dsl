#ifndef RGB__H_H___
#define RGB__H_H___

struct RGB
{
  unsigned char r, g, b;

  double red() const   { return r / 255.0; }
  double green() const { return g / 255.0; }
  double blue() const  { return b / 255.0; }

  static RGB RED()   { return {255,   0,    0}; }
  static RGB GREEN() { return {0,   255,    0}; }
  static RGB BLUE()  { return {0,     0,  255}; }

  static RGB getColor(unsigned layer)
  {
    switch (layer)
      {
      case 0: return RED();
      case 1: return GREEN();
      case 2: return BLUE();
      default:
	{
	  unsigned char r = (layer * 0xfeed) % 255;
	  unsigned char g = (layer * 0xbeef) % 255;
	  unsigned char b = (layer * 0xdead) % 255;
	  return { r, g, b };
	}		  
      }
  }
};

#endif
