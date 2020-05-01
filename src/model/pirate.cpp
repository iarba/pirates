#include "model/pirate.h"

namer_t pirate_namer = "pirate";

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
