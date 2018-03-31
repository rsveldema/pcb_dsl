#include "create_model.hpp"
#include <algorithm>
#include "utils.hpp"

void LayerMap::add(Pin *p)
{
  layer_t layer = p->get_layer();
  auto vec = usage[layer];
  vec.push_back(p);
}

void Pin::gather_layer_map(LayerMap &map)
{
  map.add(this);
}

void Component::gather_layer_map(LayerMap &map)
{
  if (info->is_board)
    {
      return;
    }
  for (unsigned ci=0;ci<pins.size();ci++)
    {
      auto pin = pins[ci];
      pin->gather_layer_map(map);
    }
}


void Model::gather_layer_map(LayerMap &map)
{
  for (auto comp : components)
    {
      comp->gather_layer_map(map);
    }
}
