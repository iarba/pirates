#ifndef MODEL_SEA_H
#define MODEL_SEA_H

#include "model/obj.h"

extern namer_t sea_namer;

class sea : public obj
{
public:
  sea();
  ~sea();
  virtual boost::property_tree::ptree serialise();
};

#endif // MODEL_SEA_H
