#ifndef MODEL_SHIP_H
#define MODEL_SHIP_H

#include "model/floater.h"

extern namer_t ship_namer;

class ship : public floater
{
public:
  static void init(boost::property_tree::ptree namer_node);
  ship(int x, int z);
  ship(boost::property_tree::ptree node);
  ~ship();
  boost::property_tree::ptree serialise();
};

#endif // MODEL_SHIP_H
