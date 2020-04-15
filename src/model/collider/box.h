#ifndef MODEL_COLLIDER_BOX_H
#define MODEL_COLLIDER_BOX_H

#include "model/collider/collider.h"

class collider_box : public collider_t
{
public:
  collider_box(physical_properties pp, double x, double z);
  double x;
  double z;
};

#endif // MODEL_COLLIDER_BOX_H
