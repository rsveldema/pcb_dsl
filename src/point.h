#ifndef POINT___H_H_H___
#define POINT___H_H_H___

#include "utils.h"

typedef unsigned layer_t;


static bool double_equals(double x1,
			 double x2)
{
  static const double EPSILON = 0.00001;
  double diff = x1 - x2;
  if (diff < 0)
    {
      diff = -diff;
    }
  return diff < EPSILON;
}
  



class Point
{
 public:
  double x, y;
  layer_t layer;

 public:
 inline Point(double _x, double _y, layer_t _layer)
    : x(grid(_x)), y(grid(_y)), layer(_layer)
    {
    }

  inline void move_to_layer(layer_t layer)
  {
    this->layer = layer;
  }

  std::string str() const
    {
      return utils::str("(", x, ", ", y, " @",layer,")");
    }

  static inline double grid(double x)
  {
    return (int(x * 256.0)) / 256.0;
  }
  
  double distance(const Point &other) const
  {
    assert(layer == other.layer);
    
    double dx = other.x - x;
    double dy = other.y - y;

    return sqrt((dx*dx) + (dy*dy));
  }

  Point max(const Point &p) const
  {
    return Point(std::max(x, p.x),
		 std::max(y, p.y),
		 layer);
  }


  void inplace_max(double _x, double _y)
  {
    x = std::max(_x, x);
    y = std::max(_y, y);
  }
  
  inline void add_inline(const Point &p)
  {
    x += p.x;
    y += p.y;
  }

  Point add(const Point &p) const
  {    
    return Point(x + p.x, y + p.y, layer);
  }

  Point sub(const Point &p) const
  {    
    return Point(x - p.x, y - p.y, layer);
  }

  Point add(const double px,
	    const double py) const
  {
    return Point(x + px, y + py, layer);
  }
  
  Point div(double d) const
  {
    return Point(x / d, y / d, layer);
  }

  Point mul(double d) const
  {
    return Point(x * d, y * d, layer);
  }

  
  static bool intersection(const Point &p1, const Point &p2,
			   const Point &p3, const Point &p4,
			   Point *ret)
  {
    // Store the values for fast access and easy
    // equations-to-code conversion
    double x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    double y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
    
    double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return false;
    
    // Get the x and y
    double pre  = (x1*y2) - (y1*x2);
    double post = (x3*y4) - (y3*x4);

    const Point hit( ( pre * (x3 - x4) - (x1 - x2) * post ) / d,
		     ( pre * (y3 - y4) - (y1 - y2) * post ) / d,
		     p1.layer);
    
    // Check if the x and y coordinates are within both lines
    if ( hit.x < std::min(x1, x2) ||
	 hit.x > std::max(x1, x2) ||
	 hit.x < std::min(x3, x4) ||
	 hit.x > std::max(x3, x4) )
      {
	return false;
      }
    
    if ( hit.y < std::min(y1, y2) ||
	 hit.y > std::max(y1, y2) ||
	 hit.y < std::min(y3, y4) ||
	 hit.y > std::max(y3, y4) )
      {
	return false;
      }
    
    if (ret)
      {
	// Return the point of intersection
	*ret = hit;
      }
    return true;
  }

  bool operator == (const Point &p) const
  {
    return
    double_equals(x, p.x) &&
    double_equals(y, p.y);
  }

  Point random_transpose(const Point &range) const
  {
    return Point(x + randrange(-range.x, range.x),
		 y + randrange(-range.y, range.y),
		 layer);
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


#endif
