#include "model/ship.h"

namer_t ship_namer = "ship";

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
