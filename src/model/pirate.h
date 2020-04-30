#ifndef MODEL_PIRATE_H
#define MODEL_PIRATE_H

#include "model/solid.h"

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
  virtual boost::property_tree::ptree serialise();
  bool owned = false;
  pirate_race_t race = pirate_neko;
};

#endif // MODEL_PIRATE_H
