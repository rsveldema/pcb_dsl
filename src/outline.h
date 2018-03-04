#ifndef OUTLINE__H_H_H__
#define OUTLINE__H_H_H__


class Outline
{
 private:
  std::vector<Point> points;
  Point cached_center;
  
 public:
  Outline()
    : cached_center(0, 0, 0)
    {
    }
  
  size_t size() const
  {
    return points.size();
  }
  
  inline layer_t get_layer() const
  {
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
  
  void drawLineTo(const Point &to,
		  Canvas *c)
  {
    RGB color = RGB::getColor(to.layer);
    c->draw_line(color, center(), to);
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


  void draw(Canvas *c,
	    const std::string &name)
  {
    if (name != "")
      {
	RGB red = {255, 0, 0};
	c->draw_text(red,
		     center(),
		     name);
      }

    const unsigned count = points.size();
    for (unsigned i = 0; i < count; i++)
      {
	Point &from = points[i];
	RGB color = RGB::getColor(from.layer);

	if (i == (count - 1))
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
    assert(points.size() == 0);
    
    points.push_back(ul);
    points.push_back(Point(lr.x, ul.y, ul.layer));
    points.push_back(lr);
    points.push_back(Point(ul.x, lr.y, ul.layer));
    compute_center();
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
  
  double getRadius() const
  {
    assert(points.size() > 0);
    return SAFE_DISTANCE_BETWEEN_COMPONENTS + center().distance(points[0]);
  }

  bool can_transpose(const Point &dir,
		     const Point &board_dim)
  {
    const unsigned count = points.size();
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
    Point c(0, 0, 0); // overwritten immediately, so we don't care about the layer here.
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
