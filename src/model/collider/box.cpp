#include "model/collider/box.h"
#include "misc_utils.h"

collider_box::collider_box(physical_properties pp, double x, double z) : collider_t(pp, c_box)
{
  this -> x = x;
  this -> z = z;
}

std::vector<glm::dvec2> collider_box::get_points()
{
  std::vector<glm::dvec2> ret;
  glm::dmat2x2 rmat = get_rotation_matrix(pp.angle);
  ret.push_back(rmat * glm::dvec2({-x / 2, -z / 2}) + pp.position);
  ret.push_back(rmat * glm::dvec2({-x / 2,  z / 2}) + pp.position);
  ret.push_back(rmat * glm::dvec2({ x / 2,  z / 2}) + pp.position);
  ret.push_back(rmat * glm::dvec2({ x / 2, -z / 2}) + pp.position);
  return ret;
}
