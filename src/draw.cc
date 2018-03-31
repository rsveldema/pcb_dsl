#include "create_model.hpp"
#include <algorithm>
#include "utils.hpp"


void Outline::drawLineTo(LineStyle style,
			 const Point &to,
			 Canvas *c)
{
  RGB color = RGB::getColor(to.layer);
  c->draw_line(style, color, center(), to);
}

void Outline::draw(Canvas *c,
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
	    c->draw_line(LineStyle::SOLID, color, from, to);
	  }
	else
	  {
	    Point &to = points[i + 1];
	    c->draw_line(LineStyle::SOLID, color, from, to);
	  }
      }
}



bool Pin::is_router_pin() const
{
  return component->info->is_router;
}

void Pin::draw(Canvas *c)
{
  if (! is_router_pin())
    {
      outline.draw(c, info->name);
    }
  for (unsigned ix = 0; ix < size(); ix++)
    {
      auto other_pin = connections[ix];

      auto style = LineStyle::SOLID;
      if (other_pin->overlaps(this))
	{
	  style = LineStyle::DASHED;
	}
      outline.drawLineTo(style,
			 other_pin->outline.center(),
			 c);
    }
}


void Component::draw(Canvas *c)
{
  if (info->is_board)
    {
      outline.draw(c, "");
    }
  else
    {
      outline.draw(c, info->name);
    }
  for (unsigned ci=0;ci<pins.size();ci++)
    {
      auto pin = pins[ci];
      pin->draw(c);
    }

  bounding_box.draw(c, "");
}


void Model::writeSVG(const std::string &filename)
{
  Canvas *canvas = Canvas::create_SVG_canvas(filename);
  draw(canvas);
  delete canvas;
}


void Model::draw(Canvas *canvas)
{
  for (auto c : components)
    {
      c->draw(canvas);
    }
}
