#include "manipulator/rays.h"

ray::ray(camera_t *camera, double x, double y, int button)
{
  double l = camera -> height * std::tan(camera -> fov / 2) * 2;
  this -> x = (x / camera -> renderer -> get_width() - 0.5) * l + camera -> position.x;
  this -> y = (y / camera -> renderer -> get_height() - 0.5) * l + camera -> position.y;
  this -> button = button;
}
