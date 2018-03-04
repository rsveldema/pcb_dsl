#include "model.h"
#include <cairomm/surface.h>
#include <cairomm/context.h>
#include <gtkmm.h>

static Glib::RefPtr<Gtk::Application> app;
static int app_argc;
static char **app_argv;


class Viewer : public Gtk::DrawingArea
{
public:
  Viewer()
  {
    //set_default_size (500, 500);
    set_has_window(false);
  }
    
public:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override
  {    
    printf("should redraw here\n");
    return true;
  }
};

class DemoWindow : public Gtk::Window
{
private:
  Viewer draw_area;
  
public:
  DemoWindow()
  {
    set_default_size (800, 600);
    set_title("pcb generator");

    add(draw_area);
    
    show_all_children();
  }
  
  ~DemoWindow()
  {
  }
}; 


/** Wrap cairo to avoid importing cairo everywhere.
 * Now cairo is used only in this file.
 */
class CairoCanvas : public Canvas
{
private:
  Cairo::RefPtr<Cairo::SvgSurface> svg;
  Cairo::RefPtr<Cairo::Context>    ctxt;

  DemoWindow *window = 0;
  
public:
  CairoCanvas()
  {
    window = new DemoWindow();
  }
  
  CairoCanvas(const std::string &filename)
  {
    svg = Cairo::SvgSurface::create(filename, 150, 150);
    ctxt = Cairo::Context::create(svg);
  }
  
public:
  virtual void draw_text(const RGB &color,
			 const Point &from,
			 const std::string &text) override
  {
    ctxt->set_source_rgb (color.red(),
			  color.green(),
			  color.blue());
    ctxt->set_line_width(0.2);
    ctxt->move_to(from.x,
		  from.y);
    ctxt->set_font_size(4);
    ctxt->show_text(text);
  }
  
  virtual void draw_line(const RGB &color,
			 const Point &from,
			 const Point &to) override
  {
    ctxt->set_source_rgb (color.red(),
			  color.green(),
			  color.blue());
    ctxt->set_line_width(0.2);
    ctxt->move_to(from.x,
		  from.y);
    ctxt->line_to(to.x,
		  to.y);
    ctxt->stroke();
  }

  virtual int run() override
  {
    return app->run(*window, app_argc, app_argv);
  }
};


Canvas *Canvas::create_SVG_canvas(const std::string &filename)
{
  return new CairoCanvas(filename);
}

Canvas *Canvas::create_canvas()
{
  return new CairoCanvas();
}


void Canvas::init(int argc, char **argv)
{
  app_argc = argc;
  app_argv = argv;
  
  app = Gtk::Application::create();
}
