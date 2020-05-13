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
  printf("generated compound around %lf %lf\n", cent.x, cent.y);
  this -> pp.position = cent;
  f1 -> pp.position -= this -> pp.position;
  f2 -> pp.position -= this -> pp.position;
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
