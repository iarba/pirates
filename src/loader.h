#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <boost/property_tree/ptree.hpp>
#include "model/obj.h"
#include <scppr.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>

typedef boost::function<void(scppr::object_t *)> load_call_t;

void handy_loader(scppr::object_t *o, glm::dvec3 position, glm::dvec3 rotation, glm::dvec3 scale, scppr::model_t *model, std::map<int, scppr::material_t> texture_overload);

namespace loader
{
  void load(std::string path);
  class namer_registry
  {
    public:
    std::map<std::string, namer_t> registry;
    std::map<std::string, scppr::material_t> textures;
    std::map<std::string, scppr::model_t *> models;
    std::map<namer_t, load_call_t> loaders;
    void bind(namer_t namer, std::string name);
    void add_texture(std::string name, scppr::material_t mat);
    void add_model(std::string name, scppr::model_t * mod);
    void bind_loader(namer_t namer, load_call_t call);
    namer_t get_namer(std::string name);
    scppr::material_t get_texture(std::string name);
    scppr::model_t *get_model(std::string name);
    void apply_loader(namer_t namer, scppr::object_t *o);
  };
  extern namer_registry name_registry;
};

#endif // LOADER_H
