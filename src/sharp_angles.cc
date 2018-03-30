#include "model.hpp"

/** returns angles in degrees (not radians)
 */
bool Component::get_connection_angle_info(InMap &in_map,
					  std::pair<double,double> &result)
{
  assert(pins.size() == 2);
  
  Pin *my_from_pin = pins[0];
  Pin *my_to_pin   = pins[1];

  bool found = false;
  double min_angle = 0;
  double max_angle = 0;

  assert(in_map.get_in(my_from_pin).size() > 0);
  assert(my_to_pin->connections.size() > 0);
  
  for (auto in : in_map.get_in(my_from_pin))
    {
      for (auto out : my_to_pin->connections)
	{
	  if (out->overlaps(in) ||
	      in->overlaps(out))
	    {
	      continue;
	    }
	  
	  assert(in != out);
	  assert(my_from_pin != in);
	  assert(my_to_pin != in);
	  assert(my_from_pin != out);
	  assert(my_to_pin != out);
	  
	  Point p3 = center();
	  Point p1 = in->center();
	  Point p2 = out->center();

	  Point v1 = p1.sub(p3);
	  Point v2 = p2.sub(p3);

	  double angleA = atan2(v2.y, v2.x) - atan2(v1.y, v1.x);
	  
	  angleA /= M_PI;
	  int angle = angleA * 180.0;
	  angle %= 360;
	  angle = abs(angle);
	  
	  if (!found)
	    {
	      found = true;
	      max_angle = min_angle = angle;
	    }
	  else
	    {
	      max_angle = std::max(max_angle, (double)angle);
	      min_angle = std::min(min_angle, (double)angle);
	    }
	}
    }
  
  result = {min_angle, max_angle};
  return found;
}

unsigned Model::get_num_sharp_angles()
{
  unsigned sharp_angles = 0;
  const unsigned num_comp = components.size();

  InMap in_map(this);
  
  for (unsigned i=0;i<num_comp;i++)
    {
      auto c = components[i];
      if (c->info->is_router)
	{
	  std::pair<double,double> angle_info;
	  if (c->get_connection_angle_info(in_map,
					   angle_info))
	    {
	      auto min = std::abs(angle_info.first);
	      auto max = std::abs(angle_info.second);
	      
	      //min = min % 180;
	      //max = max % 180;
	      
	      //printf("angle computed = %d - %d\n", min, max);
	      if (min > 0 && min < 45)
		{
		  sharp_angles++;
		}
	      else if (max > 0 && max < 45)
		{
		  sharp_angles++;
		}
	    }
	}
    }
			    
  return sharp_angles;
}

