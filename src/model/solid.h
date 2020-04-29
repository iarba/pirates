#ifndef MODEL_SOLID_H
#define MODEL_SOLID_H

#include "model/obj.h"
#include "model/physical_properties.h"

class solid : public obj
{
public:
  solid(namer_t solid_name);
  ~solid();
  physical_properties pp;
  virtual boost::property_tree::ptree serialise();
};

#endif // MODEL_SOLID_H
