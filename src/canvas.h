#ifndef CANVAS__H___
#define CANVAS__H___


enum class LineStyle
{
  SOLID, DASHED
};

/** Wrap cairo to avoid importing cairo everywhere.
 * Now it is only used inside of display.cc
 */
class Canvas
{
 public:
  virtual void draw_text(const RGB &color,
			 const MillimeterPoint &from,
			 const std::string &text) = 0;
  virtual void draw_line(LineStyle style,
			 const RGB &color,
			 const MillimeterPoint &from,
			 const MillimeterPoint &to) = 0;
  virtual void publish(Model *m) = 0;
  virtual int run() = 0;
  virtual ~Canvas() {}

  
  static void init(int argc, char **argv);
  static Canvas *create_SVG_canvas(const std::string &filename);
  static Canvas *create_canvas();
};


#endif
