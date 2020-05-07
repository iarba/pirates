#include "model/solid.h"

void solid::init(boost::property_tree::ptree namer_node)
{
}

solid::solid(namer_t solid_namer):obj(2, solid_namer)
{
}

solid::~solid()
{
}

boost::property_tree::ptree solid::serialise()
{
  boost::property_tree::ptree node = obj::serialise();
  node.put_child("pp", pp.serialise());
  return node;
}
