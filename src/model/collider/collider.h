#ifndef MODEL_COLLIDER_COLLIDER_H
#define MODEL_COLLIDER_COLLIDER_H

#include "model/physical_properties.h"

enum collider_s
{
  c_box,
  c_circle
};

class collider_t
{
public:
  collider_t(physical_properties *pp, collider_s s);
  bool collide(collider_t other, double *axis, double *offset);
  physical_properties *pp;
  collider_s s;
};

#endif // MODEL_COLLIDER_COLLIDER_H
