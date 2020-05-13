#include "model/compound.h"
#include "loader.h"

namer_t compound_namer = 0;

void compound::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.object.floater.compound");
  compound_namer = node.get<namer_t>("namer");
  loader::name_registry.bind(node.get<namer_t>("namer"), node.get<std::string>("name"));
}

compound::compound(floater *f1, floater *f2) : floater(compound_namer, f1 -> grid.x + f2 -> grid.x, f1 -> grid.z + f2 -> grid.z)
{
  add(f1);
  add(f2);
  glm::dvec2 cent = get_centroid();
  centroid_expired = true;
  perimeter_expired = true;
  this -> pp.position = cent + glm::dvec2((double)(grid.x - 1) / 2, (double)(grid.z - 1) / 2);
  f1 -> pp.position -= this -> pp.position;// - glm::dvec2((double)(f1 -> grid.x - 1) / 2, (double)(f1 ->grid.z - 1) / 2);
  f2 -> pp.position -= this -> pp.position;// - glm::dvec2((double)(f2 -> grid.x - 1) / 2, (double)(f2 ->grid.z - 1) / 2);
}

compound::compound(boost::property_tree::ptree node) : floater(node)
{
}

compound::~compound()
{
}

boost::property_tree::ptree compound::serialise()
{
  return floater::serialise();
}
