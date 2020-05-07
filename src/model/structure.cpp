#include "model/structure.h"
#include "loader.h"

namer_t structure_namer = 0;

void structure::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.object.solid.structure");
  structure_namer = node.get<namer_t>("namer");
  loader::name_registry.bind(node.get<namer_t>("namer"), node.get<std::string>("name"));
}

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
