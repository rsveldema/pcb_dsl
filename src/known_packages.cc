#include "phys.h"
#include <algorithm>
#include <string>
#include "create_model.h"

class KnownPackageInfo;
class Component;

        
std::pair<Point,Point> create_common_box(KnownPackageInfo *config,
					 Component *comp) {
  comp->info->dim =  MillimeterPoint(config->w,
				     config->h,
				     0);
  auto pos = Point();
  auto end = pos.add(MillimeterPoint(comp->info->dim.x,
				     comp->info->dim.y,
				     0));
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
      
      auto k = comp->info->dim.y / mid;
      auto starty = k * 0.25; //#this->pin_dist.mul(0.5);
      
      MillimeterLength x, y;
      if (ix >= mid)
	{
	  x = comp->info->dim.x;
	  y = starty + k * ((np-1) - ix);
	}
      else
	{
	  //#print(">>>> " + str(ix))
	  x = config->pin_len * -1;
	  y = starty + (k * ix);
	}
      
      auto pos = Point(MillimeterPoint(x, y, 0));
      auto end = pos.add(MillimeterPoint(config->pin_len, 
					 config->pin_width,
					 0));
      //#print("creating pin: " + str(p.name) + ", at " + str(pos))
      
      p->addRect(pos, end);
    }
}

static
void create_ground_poly(KnownPackageInfo *config, Component *comp)
{
  assert(comp->info->dim.x.get() > 0);
  assert(comp->info->dim.y.get() > 0);
  
  comp->info->is_ground = true;

  auto pos = Point();
  auto end = pos.add(comp->info->dim);
  comp->outline.addRect(pos,
			end);
  assert(comp->pins.size() == 1);
  comp->pins[0]->set_outline(comp->outline);
}

static
void create_single_row_pin_header(KnownPackageInfo *config, Component *comp)
{
  comp->info->dim.x  = config->w;
  comp->info->dim.y  = config->h * comp->pins.size();

  assert(comp->info->dim.x.get() > 0);
  assert(comp->info->dim.y.get() > 0);
  
  auto pos = Point();
  auto end = pos.add(comp->info->dim);
  comp->outline.addRect(pos,
			end);
  auto np = comp->pins.size();
  for (unsigned ix=0;ix<np;ix++)
    {
      auto p = comp->pins[ix];

      MillimeterLength x = 0;
      MillimeterLength y = config->h * ix;
      
      pos = Point(MillimeterPoint(x, y, 0));
      end = pos.add(MillimeterPoint(config->w,
				    config->h,
				    0));
      p->addRect(pos, end);
    }
}

void create_two_row_pin_header(KnownPackageInfo *config, Component *comp)
{
  comp->info->dim.x = config->w * 2;
  comp->info->dim.y = config->h * (comp->pins.size() / 2);
 
  auto pos = Point();
  auto end = pos.add(comp->info->dim);
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

      pos = Point(MillimeterPoint(x, y, 0));
      end = pos.add(MillimeterPoint(config->w,
				    config->h,
				    0));
      //print("creating pin: " + str(p.name) + ", at " + str(pos));
      
      p->addRect(pos, end);
    }
}

static std::vector<KnownPackageInfo*> packages = {
  	new KnownPackageInfo("ground",
			     2.35, //# w
			     2.35, // h
			     0, 0, 0,
			     create_ground_poly),
	new KnownPackageInfo("SMD condensator",            
			     2.35, //# w
			     2.35, // h
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

  fprintf(stderr, "failed to find known package: '%s'\n", name.c_str());
  abort();
}

void Component::create_outline()
{
  auto p = findKnownPackage(info->component_type);
  p->create_outline(this);
}
