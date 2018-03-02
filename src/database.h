#ifndef KNOWN_PACKAGE_H___
#define KNOWN_PACKAGE_H___

#include <string>

class Component;

class KnownPackage
{
 public:
  std::string name;

  void create_outline(Component *comp);
};

KnownPackage *findKnownPackage(const std::string &s);

#endif
