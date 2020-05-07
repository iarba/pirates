#include "model/sea.h"
#include "loader.h"

namer_t sea_namer = 0;

void sea::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.object.sea");
  sea_namer = node.get<namer_t>("namer");
  loader::name_registry.bind(node.get<namer_t>("namer"), node.get<std::string>("name"));
}

sea::sea():obj(0, sea_namer)
{
}

sea::sea(boost::property_tree::ptree node):obj(node)
{
}

sea::~sea()
{
}

boost::property_tree::ptree sea::serialise()
{
  return obj::serialise();
}
