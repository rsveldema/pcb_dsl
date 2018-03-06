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
  Viewer(CairoCanvas *c,
	 Gtk::Window *window)
  {
    this->window = window;
    this->c = c;
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

  Model *displayed_model = 0;
  DemoWindow *window = 0;
  
public:
  CairoCanvas()
  {
    window = new DemoWindow(this);
  }
  
  CairoCanvas(const std::string &filename)
  {
    svg = Cairo::SvgSurface::create(filename, 150, 150);
    ctxt = Cairo::Context::create(svg);
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
    displayed_model = m->deepclone();
    
    //fprintf(stderr, "signal!\n");
    //gtk_widget_queue_draw_area(&window->draw_area, 0, 0, 800, 600);
    //window->draw_area.queue_draw(); //signal_draw();

    window->notify();
  
    mutex.unlock();
  }

  
  virtual void draw_text(const RGB &color,
			 const Point &from,
			 const std::string &text) override
  {
    ctxt->set_source_rgb (color.red(),
			  color.green(),
			  color.blue());
    ctxt->set_line_width(0.2 * zoom);
    ctxt->move_to(from.x * zoom,
		  from.y * zoom);
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
    ctxt->set_line_width(0.2 * zoom);
    ctxt->move_to(from.x * zoom,
		  from.y * zoom);
    ctxt->line_to(to.x * zoom,
		  to.y * zoom);
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

