#ifndef MODEL_PIRATE_H
#define MODEL_PIRATE_H

#include "model/solid.h"
#include "model/collider/circle.h"

enum pirate_race_t
{
  pirate_neko
};

extern namer_t pirate_namer;

class pirate : public solid
{
public:
  pirate();
  ~pirate();
  collider_circle get_collider();
  virtual boost::property_tree::ptree serialise();
  bool owned = false;
  pirate_race_t race = pirate_neko;
};

#endif // MODEL_PIRATE_H
