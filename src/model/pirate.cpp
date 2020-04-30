#include "model/pirate.h"

namer_t pirate_namer = "pirate";

pirate::pirate():solid(pirate_namer)
{
}

pirate::~pirate()
{
}

boost::property_tree::ptree pirate::serialise()
{
  boost::property_tree::ptree node = solid::serialise();
  return node;
}
