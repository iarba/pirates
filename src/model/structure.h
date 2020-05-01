#ifndef MODEL_STRUCTURE_H
#define MODEL_STRUCTURE_H

#include "model/solid.h"
#include "model/collider/box.h"

enum structure_type_t
{
  wall,
  cannon,
  tree
};

extern namer_t structure_namer;

class structure : public solid
{
public:
  structure();
  ~structure();
  collider_box get_collider();
  virtual boost::property_tree::ptree serialise();
  structure_type_t type = wall;
};

#endif // MODEL_STRUCTURE_H
