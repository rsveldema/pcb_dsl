#include "model.h"
#include <cairomm/surface.h>
#include <cairomm/context.h>
#include <gtkmm.h>
#include <mutex>

static Glib::RefPtr<Gtk::Application> app;
static int app_argc;
static char **app_argv;

static std::mutex mutex;
class CairoCanvas;

static double zoom = 6;

class Viewer : public Gtk::DrawingArea
{
private:
  CairoCanvas *c;
  Gtk::Window *window;
  
public:
  Viewer(CairoCanvas *_c,
	 Gtk::Window *_window)
    : c(_c),
      window(_window)
  {
    //set_default_size (500, 500);
    set_has_window(false);
  }
    
public:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

class DemoWindow : public Gtk::Window
{
public:
  Viewer draw_area;
  
  Glib::Dispatcher m_Dispatcher;
  
public:
  DemoWindow(CairoCanvas *c)
    : draw_area(c, this)
  {

    // Connect the handler to the dispatcher.
    m_Dispatcher.connect(sigc::mem_fun(*this,
				       &DemoWindow::on_notification_from_worker_thread));

    
    set_default_size(800, 600);
    set_title("pcb generator");

    add(draw_area);
    
    show_all_children();
  }

  void on_notification_from_worker_thread()
  {
    draw_area.queue_draw(); //signal_draw();
  }

  
  // Called from the worker thread.
  void notify()
  {
    m_Dispatcher.emit();
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

  Model *displayed_model = NULL;
  DemoWindow *window = NULL;
  
public:
  CairoCanvas()
  {
    window = new DemoWindow(this);
  }
  
  CairoCanvas(const std::string &filename)
  {
    svg = Cairo::SvgSurface::create(filename, 1000, 1000);
    ctxt = Cairo::Context::create(svg);
  }

  virtual ~CairoCanvas()
  {
  }
  
public:
  void draw(const Cairo::RefPtr<Cairo::Context>& cr)
  {
    ctxt = cr;
    if (displayed_model)
      {
	displayed_model->draw(this);
      }
  }
  
  virtual void publish(Model *m)
  {    
    mutex.lock();    
    if (displayed_model)
      {
	delete displayed_model;
      }
    displayed_model = m->clone();
    
    //fprintf(stderr, "signal!\n");
    //gtk_widget_queue_draw_area(&window->draw_area, 0, 0, 800, 600);
    //window->draw_area.queue_draw(); //signal_draw();

    window->notify();
  
    mutex.unlock();
  }

  
  virtual void draw_text(const RGB &color,
			 const MillimeterPoint &from,
			 const std::string &text) override
  {
    ctxt->set_source_rgb (color.red(),
			  color.green(),
			  color.blue());
    ctxt->set_line_width(0.2 * zoom);
    ctxt->move_to(from.x.get() * zoom,
		  from.y.get() * zoom);
    ctxt->set_font_size(4);
    ctxt->show_text(text);
  }
  
  virtual void draw_line(const LineStyle style,
			 const RGB &color,
			 const MillimeterPoint &from,
			 const MillimeterPoint &to) override
  {
    switch (style)
      {
      case LineStyle::SOLID: ctxt->unset_dash(); break;
      case LineStyle::DASHED:
	{
	  std::vector<double> vec = {2, 2};
	  ctxt->set_dash(vec, 5);
	  break;
	}
      default: abort();
      }
    
    ctxt->set_source_rgb (color.red(),
			  color.green(),
			  color.blue());
    ctxt->set_line_width(0.2 * zoom);
    ctxt->move_to(from.x.get() * zoom,
		  from.y.get() * zoom);
    ctxt->line_to(to.x.get() * zoom,
		  to.y.get() * zoom);
    ctxt->stroke();
  }

  virtual int run() override
  {
    return app->run(*window, app_argc, app_argv);
  }
};


bool Viewer::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) 
{
  mutex.lock();
  c->draw(cr);
  mutex.unlock();
  return true;
}


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

