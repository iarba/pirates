#include "model/obj.h"
#include "model/sea.h"
#include "model/ship.h"
#include "model/island.h"

obj *obj::deserialise(boost::property_tree::ptree node)
{
  namer_t name = node.get<namer_t>("name");
  if(name == sea_namer)
  {
    return new sea(node);
  }
  if(name == ship_namer)
  {
    return new ship(node);
  }
  if(name == island_namer)
  {
    return new island(node);
  }
  return NULL;
}

obj::obj(int layer, namer_t name)
{
  this -> layer = layer;
  this -> name = name;
}

obj::obj(boost::property_tree::ptree node)
{
  this -> layer = node.get<int>("layer");
  this -> name = node.get<namer_t>("name");
  boost::property_tree::ptree children_node = node.get_child("children");
  for(auto it : children_node)
  {
    children[stoi(it.first)] = deserialise(it.second);
  }
  this -> expired = node.get<bool>("expired");
  this -> lifespan = node.get<double>("lifespan");
  this -> focused = node.get<bool>("focused");
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
  boost::property_tree::ptree children_node;
  for(auto it : children)
  {
    children_node.put_child(std::to_string(it.first), it.second -> serialise());
  }
  node.put_child("children", children_node);
  node.put("expired", expired);
  node.put("lifespan", lifespan);
  node.put("focused", focused);
  return node;
}
