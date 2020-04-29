#include "model/island.h"

namer_t island_namer = "island";

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
