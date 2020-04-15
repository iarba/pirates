#include "model/collider/collider.h"
#include "model/collider/circle.h"
#include "model/collider/box.h"

collider_t::collider_t(physical_properties *pp, collider_s s)
{
  this -> pp = pp;
  this -> s = s;
}

bool collider_t::collide(collider_t other, glm::dvec2 *axis, double *offset)
{
  return this -> collide(&other, axis, offset);
}

bool collider_t::collide(collider_t *other, glm::dvec2 *axis, double *offset)
{
  if(this -> s == c_circle && other -> s == c_circle)
  { // circle circle collision
    collider_circle *c1 = static_cast<collider_circle *>(this);
    collider_circle *c2 = static_cast<collider_circle *>(other);
    double distance = glm::distance(c1 -> pp -> position, c2 -> pp -> position);
    *offset = c1 -> r + c2 -> r - distance;
    *axis = c2 -> pp -> position - c1 -> pp -> position;
    return *offset > 0;
  }
  return false; // no collision
}
