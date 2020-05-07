#include "model/target_indicator.h"
#include "loader.h"

namer_t target_indicator_namer = 0;

void target_indicator::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.object.attachment.target_indicator");
  target_indicator_namer = node.get<namer_t>("namer");
  loader::name_registry.bind(node.get<namer_t>("namer"), node.get<std::string>("name"));
}

target_indicator::target_indicator() : attachment(target_indicator_namer)
{
}

boost::property_tree::ptree target_indicator::serialise()
{
  boost::property_tree::ptree node;
  return node;
}
