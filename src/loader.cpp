#include "loader.h"
#include "log.h"
#include <boost/property_tree/json_parser.hpp>

#include "model/obj.h"
#include "model/sea.h"
#include "model/floater.h"
#include "model/ship.h"
#include "model/island.h"
#include "model/solid.h"
#include "model/pirate.h"
#include "model/structure.h"
#include "model/attachment.h"
#include "model/highlight.h"
#include "model/target_indicator.h"

loader::namer_registry loader::name_registry;

void loader::load(std::string path)
{
  std::string directory = path.substr(0, path.find_last_of('/')) + "/";
  BOOST_LOG_TRIVIAL(info) << "opening configuration file [" << path << "]";
  boost::property_tree::ptree root;
  boost::property_tree::read_json(path, root);
  for(auto node : root)
  {
    if(node.first == "include")
    {
      load(directory + node.second.get<std::string>("target"));
    }
    if(node.first == "namer")
    {
      boost::property_tree::ptree namer_node = node.second;
      obj::init(namer_node);
      sea::init(namer_node);
      floater::init(namer_node);
      ship::init(namer_node);
      island::init(namer_node);
      solid::init(namer_node);
      pirate::init(namer_node);
      structure::init(namer_node);
      attachment::init(namer_node);
      highlight::init(namer_node);
      target_indicator::init(namer_node);
    }
  }
}

void loader::namer_registry::bind(namer_t namer, std::string name)
{
  this -> registry[name] = namer;
}
