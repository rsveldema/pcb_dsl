#include "create_model.h"
#include <algorithm>
#include "utils.h"


void Outline::drawLineTo(const Point &to,
			 Canvas *c)
{
  RGB color = RGB::getColor(to.layer);
  c->draw_line(color, center(), to);
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
	    c->draw_line(color, from, to);
	  }
	else
	  {
	    Point &to = points[i + 1];
	    c->draw_line(color, from, to);
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
  for (auto connection : connections)
    {
      outline.drawLineTo(connection->outline.center(),
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
  for (auto p : pins)
    {
      p->draw(c);
    }
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
