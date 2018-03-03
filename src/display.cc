#include "model.h"
#include <cairomm/surface.h>


using namespace Cairo;

void Model::writeSVG(const std::string &filename)
{
  auto svg = SvgSurface::create(filename, 150, 150);

  for (auto c : components)
    {
      c->writeSVG();
    }
  
  abort();
}
