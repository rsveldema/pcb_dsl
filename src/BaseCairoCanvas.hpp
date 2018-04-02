#pragma once

#include <cairomm/surface.h>
#include <cairomm/context.h>
#include <mutex>

#include "model.hpp"


class BaseWindow
{
public:
	virtual void notify() = 0;
};


/** Wrap cairo to avoid importing cairo everywhere.
* Now cairo is used only in this file.
*/
class BaseCairoCanvas : public Canvas
{
protected:
	Cairo::RefPtr<Cairo::SvgSurface> svg;
	Cairo::RefPtr<Cairo::Context>    ctxt;

	Model *displayed_model = NULL;
	BaseWindow *window = NULL;
	std::mutex &mutex;
	double zoom = 6;


public:
	BaseCairoCanvas(std::mutex &_mutex)
		: mutex(_mutex)
	{
		// a later call to create_window shall set the surface.
	}

	BaseCairoCanvas(const std::string &filename, std::mutex &_mutex)
		: mutex(_mutex)
	{
		svg = Cairo::SvgSurface::create(filename, 1000, 1000);
		ctxt = Cairo::Context::create(svg);
	}

	virtual ~BaseCairoCanvas()
	{
	}

public:
	virtual BaseWindow *create_window() = 0;

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
		window->notify();
		mutex.unlock();
	}


	virtual void draw_text(const RGB &color,
		const MillimeterPoint &from,
		const std::string &text) override
	{
		ctxt->set_source_rgb(color.red(),
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
			std::vector<double> vec = { 2, 2 };
			ctxt->set_dash(vec, 5);
			break;
		}
		default: abort();
		}

		ctxt->set_source_rgb(color.red(),
			color.green(),
			color.blue());
		ctxt->set_line_width(0.2 * zoom);
		ctxt->move_to(from.x.get() * zoom,
			from.y.get() * zoom);
		ctxt->line_to(to.x.get() * zoom,
			to.y.get() * zoom);
		ctxt->stroke();
	}
};
