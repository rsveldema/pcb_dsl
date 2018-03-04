#ifndef OUTLINE__H_H_H__
#define OUTLINE__H_H_H__


class Outline
{
 public:
  std::vector<Point> points;

  layer_t get_layer() const
  {
    assert(points.size() > 0);
    return points[0].layer;
  }
  
  void move_to_layer(layer_t layer)
  {
    for (Point &p : points)
      {
	p.move_to_layer(layer);
      }
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
    
    for (unsigned i = 0; i < points.size(); i++)
      {
	Point &from = points[i];
	RGB color = RGB::getColor(from.layer);

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
    return c.div(points.size());
  }  
};


#endif
