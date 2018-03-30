#ifndef LAYERMAP_H_H_H_
#define LAYERMAP_H_H_H_

class LayerMap
{
 private:
  std::map<layer_t, std::vector<Pin*> > usage;
  
 public:
  LayerMap() {}

  size_t size() const { return usage.size(); }
  void add(Pin *p);
};


#endif
