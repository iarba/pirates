#ifndef MODEL_PIRATE_H
#define MODEL_PIRATE_H

#include "model/solid.h"
#include "model/collider/circle.h"

typedef namer_t pirate_race_t;

extern namer_t pirate_namer;

class pirate : public solid
{
public:
  static void init(boost::property_tree::ptree namer_node);
  pirate();
  ~pirate();
  collider_circle get_collider();
  virtual boost::property_tree::ptree serialise();
  bool owned = false;
  pirate_race_t race = 0;
};

#endif // MODEL_PIRATE_H
