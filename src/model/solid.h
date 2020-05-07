#ifndef MODEL_SOLID_H
#define MODEL_SOLID_H

#include "model/obj.h"
#include "model/physical_properties.h"
#include <deque>

class solid : public obj
{
public:
  static void init(boost::property_tree::ptree namer_node);
  solid(namer_t solid_name);
  ~solid();
  physical_properties pp;
  virtual boost::property_tree::ptree serialise();
  bool targeted = false;
  std::deque<glm::dvec2> path;
};

#endif // MODEL_SOLID_H
