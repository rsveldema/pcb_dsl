#if USE_GTK
#include <gtkmm.h>

#include "BaseCairoCanvas.hpp"

static Glib::RefPtr<Gtk::Application> app;
static int app_argc;
static char **app_argv;

static std::mutex mutex;
class CairoCanvas;


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

class DemoWindow : public Gtk::Window, public BaseWindow
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
  void notify() override
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
class CairoCanvas : public BaseCairoCanvas
{  
public:
	DemoWindow * gtkwin = NULL;

public:
  CairoCanvas()
	  : BaseCairoCanvas(::mutex)
  {
  }
  
  CairoCanvas(const std::string &filename)
	  : BaseCairoCanvas(filename, ::mutex)
  {
  }
  
public: 
	BaseWindow * create_window() override
	{
		return window = gtkwin = new DemoWindow(this);
	}


  virtual int run() override
  {
    return app->run(*gtkwin, app_argc, app_argv);
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
	auto c = new CairoCanvas();
	c->create_window();
	return c;
}


void Canvas::init(int argc, char **argv)
{
  app_argc = argc;
  app_argv = argv;
  
  app = Gtk::Application::create();
}


#endif
