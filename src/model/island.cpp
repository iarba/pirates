#include "model/island.h"
#include "loader.h"

namer_t island_namer = 0;

void island::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.object.floater.island");
  island_namer = node.get<namer_t>("namer");
  loader::name_registry.bind(node.get<namer_t>("namer"), node.get<std::string>("name"));
}

island::island(int x, int z):floater(island_namer, x, z)
{
  this -> pp.inverse_mass = 0;
}

island::island(boost::property_tree::ptree node):floater(node)
{
}

island::~island()
{
}

boost::property_tree::ptree island::serialise()
{
  return floater::serialise();
}
