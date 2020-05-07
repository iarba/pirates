#include "misc_utils.h"
#include <cmath>
#include <glm/gtx/closest_point.hpp>

#define DEF_EPSILON 0.00001

bool _eq(double a, double b)
{
  return _eq(a, b, DEF_EPSILON);
}

bool _eq(glm::dvec2 a, glm::dvec2 b)
{
  return _eq(a, b, DEF_EPSILON);
}

bool _eq(double a, double b, double epsilon)
{
  return std::abs(a - b) < epsilon;
}

bool _eq(glm::dvec2 a, glm::dvec2 b, double epsilon)
{
  return _eq(a.x, b.x, epsilon) && _eq(a.y, b.y, epsilon);
}

glm::dmat2x2 get_rotation_matrix(double angle)
{
  return {{cos(angle), -sin(angle)}, {sin(angle), cos(angle)}};
}

bool point_is_in_shape(glm::dvec2 point, std::vector<glm::dvec2> shape)
{
  int i, j = shape.size() - 1;
  bool contained = false;

  for(i = 0; i < shape.size(); i++)
  {
    if(((shape[i].y < point.y && shape[j].y >= point.y) || (shape[j].y < point.y && shape[i].y >= point.y)) && (shape[i].x <= point.x || shape[j].x <= point.x))
    {
      if(shape[i].x + (point.y - shape[i].y) / (shape[j].y - shape[i].y) * (shape[j].x - shape[i].x) < point.x)
      {
        contained = !contained; 
      }
    }
    j = i; 
  }
  return contained;
}

glm::dvec2 get_edge_closest_to_point(glm::dvec2 point, std::vector<glm::dvec2> shape, glm::dvec2 *axis, double *offset)
{
  bool first = true;
  int i, j = shape.size() - 1;
  glm::dvec2 ret = {0, 0};
  for(i = 0; i < shape.size(); i++)
  {
    glm::dvec2 projected_point = glm::closestPointOnLine(point, shape[i], shape[j]);
    glm::dvec2 normal = glm::normalize(get_rotation_matrix(M_PI / 2) * (shape[j] - shape[i]));
    double distance = glm::distance(point, projected_point);
    if(first || *offset > distance)
    {
      *offset = distance;
      *axis = normal;
      ret = shape[i] - shape[j];
      first = false;
    }
    j = i;
  }
  return ret;
}

boost::property_tree::ptree vec2_to_tree(glm::dvec2 input)
{
  boost::property_tree::ptree ret;
  ret.put("x", input.x);
  ret.put("y", input.y);
  return ret;
}

boost::property_tree::ptree vec3_to_tree(glm::dvec3 input)
{
  boost::property_tree::ptree ret;
  ret.put("x", input.x);
  ret.put("y", input.y);
  ret.put("z", input.z);
  return ret;
}

glm::dvec2 tree_to_vec2(boost::property_tree::ptree input)
{
  glm::dvec2 ret;
  ret.x = input.get<double>("x");
  ret.y = input.get<double>("y");
  return ret;
}

glm::dvec3 tree_to_vec3(boost::property_tree::ptree input)
{
  glm::dvec3 ret;
  ret.x = input.get<double>("x");
  ret.y = input.get<double>("y");
  ret.z = input.get<double>("z");
  return ret;
}
