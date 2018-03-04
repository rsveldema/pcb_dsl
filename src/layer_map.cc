#include "create_model.h"
#include <algorithm>
#include "utils.h"

void LayerMap::add(Pin *p)
{
  layer_t layer = p->get_layer();
  auto vec = map[layer];
  vec.push_back(pin)
}

void Pin::gather_layer_map(LayerMap &map)
{
  map.add(this);
}

void Component::gather_layer_map(LayerMap &map)
{
  if (is_board)
    {
      return;
    }
  for (auto comp : pins)
    {
      comp->gather_layer_map(map);
    }
}


void Model::gather_layer_map(LayerMap &map)
{
  for (auto comp : components)
    {
      comp->gather_layer_map(map);
    }
}
