#include "manipulator/rays.h"

double eps = 0.1;

ray::ray(camera_t *camera, glm::dvec2 pos1, glm::dvec2 pos2, int button)
{
  double minx = std::min(pos1.x, pos2.x);
  double maxx = std::max(pos1.x, pos2.x);
  double miny = std::min(pos1.y, pos2.y);
  double maxy = std::max(pos1.y, pos2.y);
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
  this -> tl_position.x = (1.0 - maxy / w_height - 0.5) * l * height_ratio + camera -> position.x;
  this -> tl_position.y = (minx / w_width - 0.5) * l * width_ratio + camera -> position.y;
  this -> br_position.x = (1.0 - miny / w_height - 0.5) * l * height_ratio + camera -> position.x;
  this -> br_position.y = (maxx / w_width - 0.5) * l * width_ratio + camera -> position.y;
  while(br_position.x - tl_position.x < eps)
  {
    br_position.x += eps / 2.0;
    tl_position.x -= eps / 2.0;
  }
  while(br_position.y - tl_position.y < eps)
  {
    br_position.y += eps / 2.0;
    tl_position.y -= eps / 2.0;
  }
  this -> position.x = (1.0 - pos2.y / w_height - 0.5) * l * height_ratio + camera -> position.x;
  this -> position.y = (pos2.x / w_width - 0.5) * l * width_ratio + camera -> position.y;
  printf("%lf %lf <-> %lf %lf\n", tl_position.x, tl_position.y, br_position.x, br_position.y);
  this -> button = button;
}
