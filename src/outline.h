#ifndef OUTLINE__H_H_H__
#define OUTLINE__H_H_H__

#include <vector>
#include "point.h"
#include "display.h"


class Outline
{
 private:
  std::vector<Point> points;
  Point cached_center;
  
 public:
  Outline()
    {
    }

  void minmax(min_max_t &d)
  {
    for (auto p : points)
      {
	p.minmax(d);
      }
  }
  
  size_t size() const
  {
    return points.size();
  }
  
  inline layer_t get_layer() const
  {
    assert(points.size() > 0);
    assert(points[0].layer == cached_center.layer);
    return cached_center.layer; 
  }
  
  void move_to_layer(layer_t layer)
  {
    for (Point &p : points)
      {
	p.move_to_layer(layer);
      }
    cached_center.move_to_layer(layer);
  }
    
  std::string str() const
    {
      const char *prefix = "";
      std::string ret("outline<");
      for (auto p : points)
	{
	  ret += prefix;
	  ret += p.str();
	  prefix = ", ";
	}
      ret += ">";
      return ret;
    }


  void drawLineTo(const Point &to,
		  Canvas *c);
  void draw(Canvas *c,
	    const std::string &name);

  double distance(Outline &other)
  {
    return center().distance(other.center());
  }

  void addRect(const Point &ul,
	       const Point &lr)
  {
    assert(points.size() == 0);
    Dummy dummy;
    points.push_back(ul);
    points.push_back(Point(dummy, lr.x, ul.y, ul.layer));
    points.push_back(lr);
    points.push_back(Point(dummy, ul.x, lr.y, ul.layer));
    compute_center();
  }

  void rotate(double radians,
	      const Point &center)
  {
    layer_t layer = get_layer();
    const double cs = cos(radians);
    const double sn = sin(radians);    
    for (auto &p : points)
      {
	auto k = p.sub(center);
	
	double px = (k.x * cs) - (k.y * sn); 
	double py = (k.x * sn) + (k.y * cs);

	Dummy dummy;
	p = Point(dummy,
		  px + center.x,
		  py + center.y,
		  layer);	
      }
  }

  /** count the numnber of intersections when going out of the polygon.
   */
  bool point_inside_polygon(const Point &P) const
  {
    unsigned    cn = 0;
   
    const unsigned n = points.size();
    for (unsigned i = 0; i < n; i++)
      {
	unsigned ni = (i + 1) % n;
	
	if (((points[i].y <= P.y) && (points[ni].y  > P.y))  ||   
	    ((points[i].y  > P.y) && (points[ni].y <=  P.y)))
	  {
	    double vt =
	      (double)(P.y  - points[i].y) /
	      (points[ni].y - points[i].y);
	    
	    if (P.x < (points[i].x + (vt * (points[ni].x - points[i].x))))
	      {
		cn++;
	      }
	  }
      }
    return (cn & 1);
  }

  /** encloses if atleast one point of the outline is enclosed
   */
  bool partially_encloses(const Outline &c) const
  {
    for (auto p : points)
      {
	if (c.point_inside_polygon(p))
	  {
	    return true;
	  }
      }
    return false;
  }

  bool overlaps(const Outline &other) const
  {
    if (get_layer() != other.get_layer())
      {
	return false;
      }
    // now for the magic:
    if (this->partially_encloses(other))
      {
	return true;
      }
    if (other.partially_encloses(*this))
      {
	return true;
      }
    
    return false;
  }
  
  void transpose(const Point &dir)
  {
    const unsigned count = points.size();
    for (unsigned i = 0; i < count; i++)
      {
	points[i].add_inline(dir);
      }
    cached_center.add_inline(dir);
  }

  static constexpr double SAFE_DISTANCE_BETWEEN_COMPONENTS = 2;
  
  /** returns true if we'd fall off the board.
   */
  bool can_transpose(const Point &dir,
		     const Point &board_dim)
  {
    const unsigned count = points.size();
    assert(count > 0);
    for (unsigned i = 0; i < count; i++)
       {
	 if (! points[i].can_transpose(dir,
				       board_dim))
	   {
	     return false;
	   }
       }
    return true;
  }

  inline const Point &center() const
  {
    return cached_center;
  }

 private:
  void compute_center()
  {
    Point c; // overwritten immediately, so we don't care about the layer here.
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
    cached_center = c.div(points.size());
  }  
};


#endif
