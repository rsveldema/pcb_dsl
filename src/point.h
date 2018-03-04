#ifndef POINT___H_H_H___
#define POINT___H_H_H___

typedef unsigned layer_t;

class Point
{
 public:
  float x, y;
  layer_t layer;

 public:
  Point(float _x, float _y, layer_t _layer)
    : x(grid(_x)), y(grid(_y)), layer(_layer)
    {
    }

  void move_to_layer(layer_t layer)
  {
    this->layer = layer;
  }

  static inline
  double grid(double x)
  {
    return (int(x * 1000.0)) / 1000.0;
  }
  
  double distance(const Point &other)
  {
    assert(layer == other.layer);
    
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

  
  static bool intersection(const Point &p1, const Point &p2, const Point &p3, const Point &p4,
			   Point *ret)
  {
    // Store the values for fast access and easy
    // equations-to-code conversion
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
    
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return false;
    
    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
    
    // Check if the x and y coordinates are within both lines
    if ( x < std::min(x1, x2) || x > std::max(x1, x2) ||
	 x < std::min(x3, x4) || x > std::max(x3, x4) ) return false;
    if ( y < std::min(y1, y2) || y > std::max(y1, y2) ||
	 y < std::min(y3, y4) || y > std::max(y3, y4) ) return false;

    if (ret)
      {
	// Return the point of intersection
	ret->x = x;
	ret->y = y;
      }
    return true;
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
