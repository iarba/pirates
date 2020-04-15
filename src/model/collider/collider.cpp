#include "model/collider/collider.h"

collider_t::collider_t(physical_properties *pp, collider_s s)
{
  this -> pp = pp;
  this -> s = s;
}

bool collider_t::collide(collider_t other, double *axis, double *offset)
{
  return false; // no collision
}
