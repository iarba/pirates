#include "model/structure.h"

namer_t structure_namer = "structure";

structure::structure():solid(structure_namer)
{
  this -> pp.inverse_mass = 0;
}

structure::~structure()
{
}

collider_box structure::get_collider()
{
  return collider_box(pp, 0.5, 0.5);
}

boost::property_tree::ptree structure::serialise()
{
  boost::property_tree::ptree node = solid::serialise();
  return node;
}
