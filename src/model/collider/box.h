#ifndef MODEL_COLLIDER_BOX_H
#define MODEL_COLLIDER_BOX_H

#include "model/collider/collider.h"
#include <vector>
#include <glm/glm.hpp>

class collider_box : public collider_t
{
public:
  collider_box(physical_properties pp, double x, double z);
  std::vector<glm::dvec2> get_points();
  double x;
  double z;
};

#endif // MODEL_COLLIDER_BOX_H
