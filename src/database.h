#ifndef KNOWN_PACKAGE_H___
#define KNOWN_PACKAGE_H___

#include <string>
#include "point.h"

class Component;
class KnownPackageInfo;

typedef void (*handler_t)(KnownPackageInfo *self, Component *comp);


class KnownPackageInfo
{
public:
  std::string name;
  MillimeterLength w, h;
  MillimeterLength pin_len, pin_dist, pin_width;
  handler_t handler;
		   
public:
  KnownPackageInfo(const std::string &_name,
		   const MillimeterLength& _w,
		   const MillimeterLength& _h, 
		   const MillimeterLength& _pin_len,
		   const MillimeterLength& _pin_dist,
		   const MillimeterLength& _pin_width,
		   handler_t handler)
    : name(_name),
    w(_w),
    h(_h),
    pin_len(_pin_len),
    pin_dist(_pin_dist),
    pin_width(_pin_width)
  {
    this->handler = handler;
  }

  virtual void create_outline(Component *comp)
  {
    this->handler(this, comp);
  }
};



KnownPackageInfo *findKnownPackage(const std::string &s);


#endif
