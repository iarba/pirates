#include "model/structure.h"
#include "loader.h"
#include "misc_utils.h"
#include <set>

namer_t structure_namer = 0;

structure_type_t structure_default_type;

std::set<structure_type_t> shooters;

void structure::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.object.solid.structure");
  structure_namer = node.get<namer_t>("namer");
  loader::name_registry.bind(node.get<namer_t>("namer"), node.get<std::string>("name"));

  node = namer_node.get_child("base.structure");
  for(auto str : node)
  {
    namer_t namer = str.second.get<namer_t>("namer");
    try
    {
      if(str.second.get<bool>("default"))
      {
        structure_default_type = namer;
      }
    }
    catch(std::exception &e)
    {
    }
    loader::name_registry.bind(namer, str.second.get<std::string>("name"));
    try
    {
      if(str.second.get<bool>("can_shoot"))
      {
        shooters.insert(namer);
      }
    }
    catch(std::exception &e)
    {
    }
    glm::dvec3 position = tree_to_vec3(str.second.get_child("model_offset.position"));
    glm::dvec3 rotation = tree_to_vec3(str.second.get_child("model_offset.rotation"));
    glm::dvec3 scale = tree_to_vec3(str.second.get_child("model_offset.scale"));
    scppr::model_t *model = loader::name_registry.get_model(str.second.get<std::string>("model"));
    std::map<int, scppr::material_t> texture_overload;
    boost::property_tree::ptree t_node = str.second.get_child("texture");
    for(auto tex : t_node)
    {
      texture_overload[std::stoi(tex.first)] = loader::name_registry.get_texture(tex.second.get<std::string>(""));
    }
    loader::name_registry.bind_loader(namer, boost::bind(handy_loader, _1, position, rotation, scale, model, texture_overload));
  }
}

structure::structure():solid(structure_namer)
{
  this -> pp.inverse_mass = 0;
  this -> type = structure_default_type;
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

bool structure::can_shoot()
{
  return shooters.find(type) != shooters.end();
}
