#include "create_model.h"
#include <algorithm>
#include "utils.h"

bool Pin::is_router_pin() const
{
  return component->is_router;
}

void Pin::draw(Canvas *c)
{
  if (! is_router_pin())
    {
      outline.draw(c, name);
    }
  for (auto connection : connections)
    {
      outline.drawLineTo(connection->outline.center(),
			   c);
    }
}


void Component::draw(Canvas *c)
{
  outline.draw(c, name);
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
