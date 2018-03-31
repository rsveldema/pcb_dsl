#include "create_model.hpp"
#include <algorithm>
#include "utils.hpp"

void Point::rotate(double radians,
		   const Point &rotation_point)
{
  double kx = x - rotation_point.x;
  double ky = y - rotation_point.y;
  
  const double cs = cos(radians);
  const double sn = sin(radians);
  
  double px = (kx * cs) - (ky * sn); 
  double py = (kx * sn) + (ky * cs);
  
  x = px + rotation_point.x;
  y = py + rotation_point.y;
}


void Outline::rotate(double radians,
		     const Point &rotation_point)
{
  for (unsigned i=0;i<points.size();i++)
    {
      auto &p = points[i];      
      p.rotate(radians,
	       rotation_point);
    }
  cached_center.rotate(radians,
		       rotation_point);
}


void Pin::rotate(double radians,
		 const Point &rotation_point)
{
  outline.rotate(radians, rotation_point);
}


void Component::rotate(double radians)
{
  //printf("rotating %s over %f degrees\n", info->name.c_str(), radians_to_degrees(radians));
  auto rotation_point = outline.center();
  outline.rotate(radians, rotation_point);
  bounding_box.rotate(radians, rotation_point);

  for (unsigned i=0;i<pins.size();i++)
    {
      auto pin = pins[i];
      pin->rotate(radians, rotation_point);
    }
}

void Component::random_rotate()
{
  if (! info->is_rotateable)
    {
      return;
    }
  double radians = randrange(1, 8) * (M_PI / 4.0);
  rotate(radians);
}

void Model::random_rotate_component()
{
  for (auto comp : components)
    {
      comp->random_rotate();
    }
}

