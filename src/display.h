#ifndef DISPLAY___H_H__
#define DISPLAY___H_H__

#include <string>

struct RGB
{
  unsigned char r, g, b;

  double red() const   { return r / 255.0; }
  double green() const { return g / 255.0; }
  double blue() const  { return b / 255.0; }
};

class Canvas
{
 public:
  virtual void draw_text(const RGB &color,
			 const Point &from,
			 const std::string &text) = 0;
  virtual void draw_line(const RGB &color,
			 const Point &from,
			 const Point &to) = 0;
};

#endif
