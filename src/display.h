#ifndef DISPLAY___H_H__
#define DISPLAY___H_H__

#include <string>

class Model;

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


/** Wrap cairo to avoid importing cairo everywhere.
 * Now it is only used inside of display.cc
 */
class Canvas
{
 public:
  virtual void draw_text(const RGB &color,
			 const Point &from,
			 const std::string &text) = 0;
  virtual void draw_line(const RGB &color,
			 const Point &from,
			 const Point &to) = 0;
  virtual void publish(Model *m) = 0;
  virtual int run() = 0;
  virtual ~Canvas() {}

  
  static void init(int argc, char **argv);
  static Canvas *create_SVG_canvas(const std::string &filename);
  static Canvas *create_canvas();
};

#endif
