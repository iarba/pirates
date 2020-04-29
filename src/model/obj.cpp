#include "model/obj.h"

obj::obj(int layer, namer_t name)
{
  this -> layer = layer;
  this -> name = name;
}

obj::~obj()
{
  for(auto it : children)
  {
    delete it.second;
  }
}

boost::property_tree::ptree obj::serialise()
{
  boost::property_tree::ptree node;
  node.put("layer", layer);
  node.put("name", name);
  for(auto it : children)
  {
    node.put_child(std::to_string(it.first), it.second -> serialise());
  }
  node.put("expired", expired);
  node.put("lifespan", lifespan);
  node.put("focused", focused);
  return node;
}
