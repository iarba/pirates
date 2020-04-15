#ifndef MODEL_COLLIDER_CIRCLE_H
#define MODEL_COLLIDER_CIRCLE_H

#include "model/collider/collider.h"

class collider_circle : public collider_t
{
public:
  collider_circle(physical_properties pp, double r);
  double r;
};

#endif // MODEL_COLLIDER_CIRCLE_H
