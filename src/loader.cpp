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

void handy_loader(scppr::object_t *o, glm::dvec3 position, glm::dvec3 rotation, glm::dvec3 scale, scppr::model_t *model, std::map<int, scppr::material_t> texture_overload)
{
  o -> position = position;
  o -> rotation = rotation;
  o -> scale = scale;
  o -> model = model;
  o -> material_overwrite = texture_overload;
}

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
    if(node.first == "model")
    {
      std::string prefix = node.second.get<std::string>("prefix");
      node.second.erase("prefix");
      for(auto mnode : node.second)
      {
        std::string nme = prefix + mnode.second.get<std::string>("name");
        std::string pth = directory + mnode.second.get<std::string>("path");
        BOOST_LOG_TRIVIAL(info) << "adding model [" << pth << "] to " << nme;
        name_registry.add_model(nme, new scppr::model_t(pth));
      }
    }
    if(node.first == "texture")
    {
      std::string prefix = node.second.get<std::string>("prefix");
      node.second.erase("prefix");
      for(auto tnode : node.second)
      {
        scppr::material_t mat;
        std::string nme = prefix + tnode.second.get<std::string>("name");
        std::string pth = directory + tnode.second.get<std::string>("path");
        BOOST_LOG_TRIVIAL(info) << "adding texture [" << pth << "] to " << nme;
        mat.diffuse = new scppr::texture_t(pth);
        name_registry.add_texture(nme, mat);
      }
    }
  }
}

void loader::namer_registry::bind(namer_t namer, std::string name)
{
  this -> registry[name] = namer;
  BOOST_LOG_TRIVIAL(info) << "bound name " << name << " to " << namer;
}

void loader::namer_registry::add_texture(std::string name, scppr::material_t mat)
{
  this -> textures[name] = mat;
}

void loader::namer_registry::add_model(std::string name, scppr::model_t *mod)
{
  this -> models[name] = mod;
}

void loader::namer_registry::bind_loader(namer_t namer, load_call_t call)
{
  this -> loaders[namer] = call;
  BOOST_LOG_TRIVIAL(info) << "added loader to " << namer;
}

namer_t loader::namer_registry::get_namer(std::string name)
{
  auto it = this -> registry.find(name);
  if(it != this -> registry.end())
  {
    return it -> second;
  }
  throw std::logic_error("namer not found");
}
scppr::material_t loader::namer_registry::get_texture(std::string name)
{
  auto it = this -> textures.find(name);
  if(it != this -> textures.end())
  {
    return it -> second;
  }
  throw std::logic_error("texture " + name + " not found");
}

scppr::model_t *loader::namer_registry::get_model(std::string name)
{
  auto it = this -> models.find(name);
  if(it != this -> models.end())
  {
    return it -> second;
  }
  throw std::logic_error("model " + name + " not found");
}

void loader::namer_registry::apply_loader(namer_t namer, scppr::object_t *o)
{
  auto it = this -> loaders.find(namer);
  if(it != this -> loaders.end())
  {
    it -> second(o);
    return;
  }
  throw std::logic_error("namer not found");
}
