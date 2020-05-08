#include "model/target_indicator.h"
#include "loader.h"
#include "misc_utils.h"

namer_t target_indicator_namer = 0;

void target_indicator::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.object.attachment.target_indicator");
  target_indicator_namer = node.get<namer_t>("namer");
  loader::name_registry.bind(node.get<namer_t>("namer"), node.get<std::string>("name"));
  glm::dvec3 position = tree_to_vec3(node.get_child("model_offset.position"));
  glm::dvec3 rotation = tree_to_vec3(node.get_child("model_offset.rotation"));
  glm::dvec3 scale = tree_to_vec3(node.get_child("model_offset.scale"));
  scppr::model_t *model = loader::name_registry.get_model(node.get<std::string>("model"));
  std::map<int, scppr::material_t> texture_overload;
  boost::property_tree::ptree t_node = node.get_child("texture");
  for(auto tex : t_node)
  {
    texture_overload[std::stoi(tex.first)] = loader::name_registry.get_texture(tex.second.get<std::string>(""));
  }
  loader::name_registry.bind_loader(target_indicator_namer, boost::bind(handy_loader, _1, position, rotation, scale, model, texture_overload));
}

target_indicator::target_indicator() : attachment(target_indicator_namer)
{
}

boost::property_tree::ptree target_indicator::serialise()
{
  boost::property_tree::ptree node;
  return node;
}
