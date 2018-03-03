#ifndef PHYS__G_H___
#define PHYS__G_H___

#include <assert.h>
#include <math.h>
#include <vector>


static inline
float grid(float x)
{
  return (int(x * 100.0)) / 100.0;
}


class Point
{
 public:
  float x, y;
  unsigned layer;

 public:
  Point(float _x, float _y, unsigned _layer)
    : x(grid(_x)), y(grid(_y)), layer(_layer)
    {
    }
  
  double distance(const Point &other)
  {
    double dx = other.x - x;
    double dy = other.y - y;

    return sqrt((dx*dx) + (dy*dy));
  }

  
  Point add(const Point &p) const
  {
    return Point(x + p.x, y + p.y, layer);
  }

  Point add(const float px,
	    const float py)
  {
    return Point(x + px, y + py, layer);
  }
  
  Point div(float d) const
  {
    return Point(x / d, y / d, layer);
  }

  Point mul(float d) const
  {
    return Point(x * d, y * d, layer);
  }
  
  bool can_transpose(const Point &dir, const Point &max) const
  {
    Point k = add(dir);
    if (k.x < 0) return false;
    if (k.y < 0) return false;
    if (k.x > max.x) return false;
    if (k.y > max.y) return false;
    return true;
  }
};

#include "display.h"

class Outline
{
 public:
  std::vector<Point> points;

  RGB getColor(int layer)
  {
    return {0, 255, 0};
  }

  void drawLineTo(const Point &to,
		  Canvas *c)
  {
    RGB color = getColor(to.layer);
    c->draw_line(color, center(), to);
  }

  void draw(Canvas *c,
	    const std::string &name)
  {
    if (name != "")
      {
	RGB red = {255, 0, 0};
	c->draw_text(red,
		     points[0],
		     name);
      }
    
    for (unsigned i = 0; i < points.size(); i++)
      {
	Point &from = points[i];
	RGB color = getColor(from.layer);

	if (i == (points.size() - 1))
	  {
	    Point &to = points[0];
	    c->draw_line(color, from, to);
	  }
	else
	  {
	    Point &to = points[i + 1];
	    c->draw_line(color, from, to);
	  }
      }
  }
  
  double distance(Outline &other)
  {
    return center().distance(other.center());
  }

  void addRect(const Point &ul,
	       const Point &lr)
  {
    points.push_back(ul);
    points.push_back(Point(lr.x, ul.y, ul.layer));
    points.push_back(lr);
    points.push_back(Point(ul.x, lr.y, ul.layer));
  }
  
  void transpose(const Point &dir)
  {
    for (unsigned i = 0; i < points.size(); i++)
      {
	points[i] = points[i].add(dir);
      }
  }

  double getRadius() const
  {
    assert(points.size() > 0);
    return center().distance(points[0]);
  }

  bool can_transpose(const Point &dir,
		     const Point &board_dim)
  {
    for (auto p : points)
      {
	if (! p.can_transpose(dir,
			      board_dim))
	  {
	    return false;
	  }
      }
    return true;
  }
  
  Point center() const
  {
    Point c(0,0,0);
    bool first = true;
    for (auto p : points)
      {
	if (first)
	  {
	    first = false;
	    c = p;
	  }
	else
	  {
	    c = c.add(p);
	  }
      }
    return c.div(points.size());
  }  
};

#endif
