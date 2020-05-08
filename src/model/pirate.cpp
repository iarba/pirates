#include "model/pirate.h"
#include "loader.h"
#include "misc_utils.h"

namer_t pirate_namer = 0;
pirate_race_t pirate_default_race = 0;

void pirate::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.object.solid.pirate");
  pirate_namer = node.get<namer_t>("namer");
  loader::name_registry.bind(pirate_namer, node.get<std::string>("name"));
  
  node = namer_node.get_child("base.race");
  for(auto rac : node)
  {
    namer_t namer = rac.second.get<namer_t>("namer");
    try
    {
      if(rac.second.get<bool>("default"))
      {
        pirate_default_race = namer;
      }
    }
    catch(std::exception &e)
    {
    }
    loader::name_registry.bind(namer, rac.second.get<std::string>("name"));
    glm::dvec3 position = tree_to_vec3(rac.second.get_child("model_offset.position"));
    glm::dvec3 rotation = tree_to_vec3(rac.second.get_child("model_offset.rotation"));
    glm::dvec3 scale = tree_to_vec3(rac.second.get_child("model_offset.scale"));
    scppr::model_t *model = loader::name_registry.get_model(rac.second.get<std::string>("model"));
    std::map<int, scppr::material_t> texture_overload;
    boost::property_tree::ptree t_node = rac.second.get_child("texture");
    for(auto tex : t_node)
    {
      texture_overload[std::stoi(tex.first)] = loader::name_registry.get_texture(tex.second.get<std::string>(""));
    }
    loader::name_registry.bind_loader(namer, boost::bind(handy_loader, _1, position, rotation, scale, model, texture_overload));
  }
}

pirate::pirate():solid(pirate_namer)
{
  race = pirate_default_race;
}

pirate::~pirate()
{
}

collider_circle pirate::get_collider()
{
  return collider_circle(pp, 0.5);
}

boost::property_tree::ptree pirate::serialise()
{
  boost::property_tree::ptree node = solid::serialise();
  return node;
}
