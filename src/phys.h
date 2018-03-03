#ifndef PHYS__G_H___
#define PHYS__G_H___

#include <math.h>
#include <vector>

class Point
{
 public:
  float x, y;
  unsigned layer;

 public:
  Point(float _x, float _y, unsigned _layer)
    : x(_x), y(_y), layer(_layer)
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

class Outline
{
 public:
  std::vector<Point> points;

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

  double getRadius()
  {
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
	    c = p;
	  }
	else
	  {
	    p = c.add(p);
	  }
      }
    return c.div(points.size());
  }  
};

#endif
