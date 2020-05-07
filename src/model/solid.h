#ifndef MODEL_SOLID_H
#define MODEL_SOLID_H

#include "model/obj.h"
#include "model/physical_properties.h"
#include <vector>

class solid : public obj
{
public:
  solid(namer_t solid_name);
  ~solid();
  physical_properties pp;
  virtual boost::property_tree::ptree serialise();
  bool targeted = false;
  std::vector<glm::dvec2> path;
  glm::dvec2 target;
};

#endif // MODEL_SOLID_H
