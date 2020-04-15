#include "model/collider/box.h"

collider_box::collider_box(physical_properties *pp, double x, double z) : collider_t(pp, c_box)
{
  this -> x = x;
  this -> z = z;
}
