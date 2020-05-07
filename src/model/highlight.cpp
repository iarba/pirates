#include "model/highlight.h"
#include "loader.h"

namer_t highlight_namer = 0;

void highlight::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.object.attachment.highlight");
  highlight_namer = node.get<namer_t>("namer");
  loader::name_registry.bind(node.get<namer_t>("namer"), node.get<std::string>("name"));
}

highlight::highlight() : attachment(highlight_namer)
{
}

boost::property_tree::ptree highlight::serialise()
{
  boost::property_tree::ptree node;
  return node;
}
