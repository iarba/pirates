#include "model/pirate.h"
#include "loader.h"

namer_t pirate_namer = 0;

void pirate::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.object.solid.pirate");
  pirate_namer = node.get<namer_t>("namer");
  loader::name_registry.bind(node.get<namer_t>("namer"), node.get<std::string>("name"));
}

pirate::pirate():solid(pirate_namer)
{
}

pirate::~pirate()
{
}

collider_circle pirate::get_collider()
{
  return collider_circle(pp, 0.5);
}

boost::property_tree::ptree pirate::serialise()
{
  boost::property_tree::ptree node = solid::serialise();
  return node;
}
