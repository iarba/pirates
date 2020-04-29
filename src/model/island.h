#ifndef MODEL_ISLAND_H
#define MODEL_ISLAND_H

#include "model/floater.h"

extern namer_t island_namer;

class island : public floater
{
public:
  island(int x, int z);
  island(boost::property_tree::ptree node);
  ~island();
  boost::property_tree::ptree serialise();
};

#endif // MODEL_ISLAND_H
