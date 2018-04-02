#if !USE_GTK

#include "model.hpp"

class WindowsCanvas : public Canvas
{
public:
	virtual void draw_text(const RGB &color,
		const MillimeterPoint &from,
		const std::string &text)
	{
	}

	virtual void draw_line(LineStyle style,
		const RGB &color,
		const MillimeterPoint &from,
		const MillimeterPoint &to)
	{
	}
	virtual void publish(Model *m)
	{
	}
	virtual int run()
	{
		return 0;
	}
};

Canvas *Canvas::create_SVG_canvas(const std::string &filename)
{
	return nullptr;
}

Canvas *Canvas::create_canvas()
{
	return new WindowsCanvas();
}


void Canvas::init(int argc, char **argv)
{
}


#endif