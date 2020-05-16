#ifndef MODEL_STRUCTURE_H
#define MODEL_STRUCTURE_H

#include "model/solid.h"
#include "model/collider/box.h"

typedef namer_t structure_type_t;

extern namer_t structure_namer;

class structure : public solid
{
public:
  static void init(boost::property_tree::ptree namer_node);
  structure();
  ~structure();
  collider_box get_collider();
  virtual boost::property_tree::ptree serialise();
  bool can_shoot();
  structure_type_t type;
};

#endif // MODEL_STRUCTURE_H
