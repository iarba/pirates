#ifndef MODEL_COLLIDER_COLLIDER_H
#define MODEL_COLLIDER_COLLIDER_H

#include "model/physical_properties.h"
#include <glm/glm.hpp>

enum collider_s
{
  c_box,
  c_circle
};

class collider_t
{
public:
  collider_t(physical_properties *pp, collider_s s);
  bool collides(collider_t *other, glm::dvec2 *axis, double *offset);
  physical_properties *pp;
  collider_s s;
};

#endif // MODEL_COLLIDER_COLLIDER_H
