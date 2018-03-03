#include "model.h"
#include <cairomm/surface.h>
#include <cairomm/context.h>




class CairoCanvas : public Canvas
{
private:
  Cairo::RefPtr<Cairo::SvgSurface> svg;
  Cairo::RefPtr<Cairo::Context>    ctxt;
  
public:
  CairoCanvas(const std::string &filename)
  {
    svg = Cairo::SvgSurface::create(filename, 150, 150);
    ctxt = Cairo::Context::create(svg);
  }
  
public:
  virtual void draw_text(const RGB &color,
			 const Point &from,
			 const std::string &text)
  {
    ctxt->move_to(from.x,
		  from.y);
    ctxt->show_text(text);
  }
  
  virtual void draw_line(const RGB &color,
			 const Point &from,
			 const Point &to)
  {
    ctxt->move_to(from.x,
		  from.y);
    ctxt->line_to(to.x,
		  to.y);
  }
};

void Model::writeSVG(const std::string &filename)
{
  CairoCanvas canvas(filename);

  for (auto c : components)
    {
      c->draw(&canvas);
    }
}
