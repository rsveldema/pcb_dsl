#ifndef KNOWN_PACKAGE_H___
#define KNOWN_PACKAGE_H___

#include <string>

class Component;
class KnownPackageInfo;

typedef void (*handler_t)(KnownPackageInfo *self, Component *comp);


class KnownPackageInfo
{
public:
  std::string name;
  float w;
  float h;
  float pin_len;
  float pin_dist;
  float pin_width;
  handler_t handler;
		   
public:
  KnownPackageInfo(const std::string &name,
		   float w, float h, float pin_len, float pin_dist, float pin_width,
		   handler_t handler)
  {
    this->name = name;
    this->w = w;
    this->h = h;
    this->pin_len = pin_len;
    this->pin_dist = pin_dist;
    this->pin_width = pin_width;
    this->handler = handler;
  }

  virtual void create_outline(Component *comp)
  {
    this->handler(this, comp);
  }
};



KnownPackageInfo *findKnownPackage(const std::string &s);


#endif
