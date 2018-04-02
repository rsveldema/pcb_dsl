#ifndef OUTLINE__H_H_H__
#define OUTLINE__H_H_H__

#include "my_vector.hpp"


#include "point.hpp"
#include "display.hpp"


class Outline
{
private:
  static constexpr unsigned MAX_POINTS_PER_OUTLINE = 4;
  
  fixedsize_vector<Point, MAX_POINTS_PER_OUTLINE> points;
  Point cached_center;
  
 public:
  Outline()
    {
    }

  void minmax(min_max_t &d)
  {
    for (unsigned i=0;i<points.size();i++)
      {
	auto &p = points[i];
	p.minmax(d);
      }
  }

  size_t size() const
  {
	  return points.size();
  }

  const Point &get(unsigned ix) const
  {
	  return points[ix];
  }

  inline layer_t get_layer() const
  {
    assert(points.size() > 0);
    assert(points[0].layer == cached_center.layer);
    return cached_center.layer; 
  }
  
  void set_layer(layer_t layer)
  {
    for (unsigned i=0;i<points.size();i++)
      {
	auto &p = points[i];
	p.set_layer(layer);
      }
    cached_center.set_layer(layer);
  }
    
  std::string str() const
  {
    const char *prefix = "";
    std::string ret("outline<");
    for (unsigned i=0;i<points.size();i++)
      {
	auto &p = points[i];
	
	ret += prefix;
	ret += p.str();
	prefix = ", ";
      }
    ret += ">";
    return ret;
  }
  

  void drawLineTo(LineStyle style,
		  const Point &to,
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
	      const Point &center);

  bool intersects_line(const Point &p1,
		       const Point &p2) const
  {
    if (get_layer() != p1.get_layer())
      {
	return false;
      }
    
    const unsigned n = points.size();
    for (unsigned i = 0; i < n; i++)
      {
	const Point &a = points[i];
	const Point &b = points[(i + 1) % points.size()];
	if (Point::intersection(a, b,
				p1, p2,
				NULL))
	  {
	    return true;
	  }
      }
    return false;
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
    for (unsigned i=0;i<points.size();i++)
      {
	auto &p = points[i];

	if (c.point_inside_polygon(p))
	  {
	    return true;
	  }
      }
    return false;
  }

  bool have_crossing_lines(const Point &op1,
			   const Point &op2) const
  {
    const unsigned n = points.size();
    for (unsigned i = 0; i < n; i++)
      {
	unsigned ni = (i + 1) % n;

	auto &p1 = points[i];
	auto &p2 = points[ni];

	if (Point::intersection(p1, p2,
				op1, op2,
				NULL))
	  {
	    return true;
	  }
      }
    
    return false;
  }

  bool have_crossing_lines(const Outline &other) const
  {
    const unsigned n = points.size();
    for (unsigned i = 0; i < n; i++)
      {
	unsigned ni = (i + 1) % n;

	auto &p1 = points[i];
	auto &p2 = points[ni];

	if (other.have_crossing_lines(p1, p2))
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
    return have_crossing_lines(other);
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

    for (unsigned i=0;i<points.size();i++)
      {
	auto &p = points[i];
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
