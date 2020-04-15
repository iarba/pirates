#include "misc_utils.h"
#include <cmath>

#define EPSILON 0.00001

bool _eq(double a, double b)
{
  return std::abs(a - b) < EPSILON;
}

bool _eq(glm::dvec2 a, glm::dvec2 b)
{
  return _eq(a.x, b.x) && _eq(a.y, b.y);
}

glm::mat2x2 get_rotation_matrix(double angle)
{
  return {{cos(angle), -sin(angle)}, {sin(angle), cos(angle)}};
}