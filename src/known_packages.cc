#include "phys.h"
#include <algorithm>
#include <string>
#include "create_model.h"

class KnownPackageInfo;
class Component;

        
std::pair<Point,Point> create_common_box(KnownPackageInfo *config, Component *comp) {
  comp->dim.x = config->w;
  comp->dim.y = config->h;
  auto pos = Point(0, 0, 0);
  auto end = pos.add(comp->dim.x,
		     comp->dim.y);
  comp->outline.addRect(pos,
			end);
  //print("created: " + str(comp->outline))
  return {pos, end};
}


void create_pins_RS28(KnownPackageInfo *config, Component *comp) {
  //auto pr =
  create_common_box(config, comp);
  //auto pos = pr.first;
  //auto end = pr.second;
      
  auto np = comp->pins.size();
  for (unsigned ix = 0; ix < np; ix++)
    {
      auto p = comp->pins[ix];
      
      //#print("creating pin: " + str(p.name))
      
      auto mid = comp->pins.size() / 2;
      
      auto k = comp->dim.y / mid;
      auto starty = k * 0.25; //#this->pin_dist.mul(0.5);
      
      float x, y;
      if (ix >= mid) {
	x = comp->dim.x;
	y = starty + k * ((np-1) - ix);
      } else {
	//#print(">>>> " + str(ix))
	x = config->pin_len * -1;
	y = starty + (k * ix);
      }
      
      auto pos = Point(x, y, 0);
      auto end = pos.add(config->pin_len, config->pin_width);
      //#print("creating pin: " + str(p.name) + ", at " + str(pos))
      
      p->outline.addRect(pos, end);
    }
}

void create_single_row_pin_header(KnownPackageInfo *config, Component *comp) {
  comp->dim.x  = config->w;
  comp->dim.y  = config->h * comp->pins.size();
  auto pos = Point(0, 0, 0);
  auto end = pos.add(comp->dim.x,
		     comp->dim.y);
  comp->outline.addRect(pos,
			end);
  auto np = comp->pins.size();
  for (unsigned ix=0;ix<np;ix++)
    {
      auto p = comp->pins[ix];
        
      float x = 0;
      float y = config->h * ix;
      
      pos = Point(x, y, 0);
      end = pos.add(config->w, config->h);
      //#print("creating pin: " + str(p.name) + ", at " + str(pos))
	
      p->outline.addRect(pos, end);
    }
}

void create_two_row_pin_header(KnownPackageInfo *config, Component *comp)
{
  comp->dim.x  = config->w * 2;
  comp->dim.y = config->h * (comp->pins.size() / 2);
  auto pos = Point(0, 0, 0);
  auto end = pos.add(comp->dim.x,
		     comp->dim.y);
  comp->outline.addRect(pos,
			end);
  
  auto np = comp->pins.size();

  for (unsigned ix=0;ix<np;ix++)
    {
      auto p = comp->pins[ix];
      
      auto ix1 = (ix % 2);
      auto ix2 = int(ix / 2); 
      auto x = config->w * (ix1);
      auto y = config->h * (ix2);

      pos = Point(x, y, 0);
      end = pos.add(config->w, config->h);
      //print("creating pin: " + str(p.name) + ", at " + str(pos));
      
      p->outline.addRect(pos, end);
    }
}

std::vector<KnownPackageInfo*> packages = {
	new KnownPackageInfo("ground",            
			     2.35, //# w
			     2.35, //# h
			     0, 0, 0,
			     create_single_row_pin_header),
	new KnownPackageInfo("SMD condensator",            
			     2.35, //# w
								      2.35, //// h
			     0, 0, 0,
			     create_single_row_pin_header),
	new KnownPackageInfo("SMD resistor",            
			     2.35, // w
			     2.35, // h
			     0, 0, 0,
			     create_single_row_pin_header),
	new KnownPackageInfo("single row pin header",            
			     2.35, // w
			     2.35, // h
			     0, 0, 0,
			     create_single_row_pin_header),
	new KnownPackageInfo("two row pin header",            
			     2.35, // w
			     2.35, // h
			     0, 0, 0,
			     create_two_row_pin_header),
	new KnownPackageInfo("RS-28",
			     5.38, // w
			     10.34, // h
			     1.26, // pin-len
			     0.65, // pin-dist
			     0.38,// pin-width
			     create_pins_RS28)
      };


KnownPackageInfo* findKnownPackage(const std::string &name)
{
  for (auto p : packages)
    {
      if (p->name == name)
	{
	  return p;
	}
    }
  
  abort();
}



void Component::create_outline()
{
  auto p = findKnownPackage(component_type);
  p->create_outline(this);
}
