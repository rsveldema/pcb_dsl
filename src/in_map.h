#ifndef IN_PIN_MAP__H____
#define IN_PIN_MAP__H____

#include <assert.h>
#include <map>
#include <vector>

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

  std::vector<Pin*> &get_in(Pin *to)
  {
    assert(map.find(to) != map.end());
    return map[to];
  }
  
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
