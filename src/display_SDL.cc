#if ! USE_GTK

#include "BaseCairoCanvas.hpp"

#include "SDL2/SDL.h"

static std::mutex mutex;
static std::condition_variable cv;
class WinCairoCanvas;

class SDLWindow
{
protected:
	int width, height;

	SDL_Window *window;


	SDL_Surface *screen;
	const char *title;
public:
	SDLWindow(int w, int h, const char *title)
	{
		this->width = w;
		this->height = h;
		this->title = title;
		
		// Create an application window with the following settings:
		window = SDL_CreateWindow(
			"An SDL2 window",                  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			w,                               // width, in pixels
			h,                               // height, in pixels
			SDL_WINDOW_SHOWN                   // flags - see below
		);

		screen = SDL_GetWindowSurface(window);
	}

	void copy_cairo_surface_to_screen()
	{
		//	SDL_BlitSurface(sdlsurf, NULL, screen, NULL); // blit it to the screen
		SDL_UpdateWindowSurface(window);
	}

	void clear()
	{
		/* Prefilling the surface tests the mark_dirty functions. */
		SDL_FillRect(screen, NULL,
			SDL_MapRGBA(screen->format, 192, 192, 192, 255));
	}

	void lock()
	{
		SDL_LockSurface(screen);
	}
	void unlock()
	{
		SDL_UnlockSurface(screen);
	}
};

class DemoWindow : public SDLWindow, public BaseWindow
{
public:
	std::shared_ptr<Cairo::ImageSurface> cairo_surface;

public:
	DemoWindow(WinCairoCanvas *c)
		: SDLWindow(800, 600, "pcb generator")
	{
		cairo_surface = Cairo::ImageSurface::create((unsigned char*) (screen->pixels),
				Cairo::Format::FORMAT_RGB24,// CAIRO_FORMAT_RGB24,
				screen->w,
				screen->h,
				screen->pitch);
	}

	// Called from the worker thread.
	void notify() override
	{
		cv.notify_all();
	}


	~DemoWindow()
	{
	}
};


/** Wrap cairo to avoid importing cairo everywhere.
* Now cairo is used only in this file.
*/
class WinCairoCanvas : public BaseCairoCanvas
{
public:
	DemoWindow * gtkwin = NULL;

public:
	WinCairoCanvas()
		: BaseCairoCanvas(::mutex)
	{
	}

	WinCairoCanvas(const std::string &filename)
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
		while (1)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
			}

			auto duration = std::chrono::microseconds(100);

			std::unique_lock<std::mutex> lk(::mutex);
			cv.wait_for(lk, duration);
			gtkwin->lock();
			gtkwin->clear();
			assert(gtkwin);

			auto cairo_ctxt = Cairo::Context::create(gtkwin->cairo_surface);
			draw(cairo_ctxt);		
			
			gtkwin->copy_cairo_surface_to_screen();
			gtkwin->unlock();
		}
		return 0;
	}
};



Canvas *Canvas::create_SVG_canvas(const std::string &filename)
{
	return new WinCairoCanvas(filename);
}

Canvas *Canvas::create_canvas()
{
	auto c = new WinCairoCanvas();
	c->create_window();
	return c;
}


void Canvas::init(int argc, char **argv)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
	atexit(SDL_Quit);
}


#endif