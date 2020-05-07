#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <boost/property_tree/ptree.hpp>
#include "model/obj.h"

namespace loader
{
  void load(std::string path);
  class namer_registry
  {
    public:
    std::map<std::string, namer_t> registry;
    void bind(namer_t namer, std::string name);
  };
  extern namer_registry name_registry;
};

#endif // LOADER_H
