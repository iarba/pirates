#include "model/collider/circle.h"

collider_circle::collider_circle(physical_properties pp, double r) : collider_t(pp, c_circle)
{
  this -> r = r;
}
