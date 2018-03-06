#ifndef IN_PIN_MAP__H____
#define IN_PIN_MAP__H____

class Pin;
class Model;

/** retrieve the incoming edges from a pin.
 */
class InMap
{
private:
  std::map<Pin*, std::vector<Pin*>> map;

  void add_in(Pin *from, Pin *to)
  {
    if (map.find(to) == map.end())
      {
	map[to] = {from};
      }
    else
      {
	map[to].push_back(from);
      }
  }

public:
  InMap(Model *m);
  
  unsigned num_incoming_edges(Pin *pin)
  {
    // if not in map, pin was unused.
    if (map.find(pin) == map.end())
      {
	return 0;
      }
    return map[pin].size();
  }
};


#endif 
