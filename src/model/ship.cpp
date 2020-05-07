#include "model/ship.h"
#include "loader.h"

namer_t ship_namer = 0;

void ship::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.object.floater.ship");
  ship_namer = node.get<namer_t>("namer");
  loader::name_registry.bind(node.get<namer_t>("namer"), node.get<std::string>("name"));
}

ship::ship(int x, int z):floater(ship_namer, x, z)
{
}

ship::ship(boost::property_tree::ptree node):floater(node)
{
}

ship::~ship()
{
}

boost::property_tree::ptree ship::serialise()
{
  return floater::serialise();
}
