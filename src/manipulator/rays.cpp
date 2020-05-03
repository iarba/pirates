#include "manipulator/rays.h"

ray::ray(camera_t *camera, double x, double y, int button)
{
  double w_height = camera -> renderer -> get_height();
  double w_width = camera -> renderer -> get_width();
  double width_ratio = 1;
  double height_ratio = 1;
  if(w_height > w_width)
  {
    height_ratio = w_height / w_width;
  }
  if(w_width > w_height)
  {
    width_ratio = w_width / w_height;
  }
  double l = camera -> height * std::tan(camera -> fov / 2) * 2;
  this -> position.x = (1.0 - y / w_height - 0.5) * l * height_ratio + camera -> position.x;
  this -> position.y = (x / w_width - 0.5) * l * width_ratio + camera -> position.y;
  this -> button = button;
}
