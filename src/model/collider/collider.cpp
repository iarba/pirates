#include "model/collider/collider.h"
#include "model/collider/circle.h"
#include "model/collider/box.h"
#include "misc_utils.h"

collider_t::collider_t(physical_properties pp, collider_s s)
{
  this -> pp = pp;
  this -> s = s;
}

bool collider_t::collides(collider_t *other, glm::dvec2 *axis, double *offset)
{
  if(this -> s == c_circle && other -> s == c_circle)
  { // circle circle collision
    collider_circle *c1 = static_cast<collider_circle *>(this);
    collider_circle *c2 = static_cast<collider_circle *>(other);
    double distance = glm::distance(c1 -> pp.position, c2 -> pp.position);
    *offset = c1 -> r + c2 -> r - distance;
    *axis = c2 -> pp.position - c1 -> pp.position;
    if(_eq(*axis, {0, 0}))
    {
      *axis = {0, 1}; // TODO: random
    }
    *axis = glm::normalize(*axis);
    return *offset > 0;
  }
  if(this -> s == c_box && other -> s == c_box)
  { // box box collision
    collider_box *b1 = static_cast<collider_box *>(this);
    collider_box *b2 = static_cast<collider_box *>(other);
    std::vector<glm::dvec2> points1 = b1 -> get_points();
    std::vector<glm::dvec2> points2 = b2 -> get_points();
    // use SAT
    glm::dmat2x2 normal_rotation = get_rotation_matrix(M_PI / 2);
    glm::dvec2 axi[4] = {
      normal_rotation * (points1[0] - points1[1]),
      normal_rotation * (points1[0] - points1[3]),
      normal_rotation * (points2[0] - points2[1]),
      normal_rotation * (points2[0] - points2[3])
    };
    for(int i = 0; i < 4; i++)
    {
      axi[i] = glm::normalize(axi[i]);
      double min1p, max1p, min2p, max2p;
      // project shape 1 onto axis
      bool first = true;
      for(auto point : points1)
      {
        double p = glm::dot(axi[i], point);
        if(first)
        {
          min1p = p;
          max1p = p;
          first = false;
          continue;
        }
        else
        {
          min1p = std::min(min1p, p);
          max1p = std::max(max1p, p);
        }
      }
      // project shape 2 onto axis
      first = true;
      for(auto point : points2)
      {
        double p = glm::dot(axi[i], point);
        if(first)
        {
          min2p = p;
          max2p = p;
          first = false;
          continue;
        }
        else
        {
          min2p = std::min(min2p, p);
          max2p = std::max(max2p, p);
        }
      }
      if((max2p > min1p) && (max1p > min2p))
      { // collides on this axis
        double projection_difference = std::min(max2p - min1p, max1p - min2p);
        if(i == 0)
        {
          *offset = projection_difference;
          *axis = axi[i];
        }
        if(*offset > projection_difference)
        {
          *offset = projection_difference;
          *axis = axi[i];
        }
      }
      else
      { // no collision on this axis
        return false;
      }
    }
    return !_eq(*offset, 0);
  }
  if(this -> s == c_circle && other -> s == c_box)
  {
    bool ret = other -> collides(this, axis, offset);
    *axis *= -1;
    return ret;
  }
  if(this -> s == c_box && other -> s == c_circle)
  { // box box collision
    collider_box *b = static_cast<collider_box *>(this);
    collider_circle *c = static_cast<collider_circle *>(other);
    std::vector<glm::dvec2> points = b -> get_points();
    // use SAT
    glm::dmat2x2 normal_rotation = get_rotation_matrix(M_PI / 2);
    glm::dvec2 axi[3] = {
      normal_rotation * (points[0] - points[1]),
      normal_rotation * (points[0] - points[3]),
      b -> pp.position - c -> pp.position
    };
    for(int i = 0; i < 3; i++)
    {
      axi[i] = glm::normalize(axi[i]);
      double min1p, max1p, min2p, max2p;
      // project shape 1 onto axis
      bool first = true;
      for(auto point : points)
      {
        double p = glm::dot(axi[i], point);
        if(first)
        {
          min1p = p;
          max1p = p;
          first = false;
          continue;
        }
        else
        {
          min1p = std::min(min1p, p);
          max1p = std::max(max1p, p);
        }
      }
      // project shape 2 onto axis
      double pc = glm::dot(axi[i], c -> pp.position);
      min2p = pc - c -> r;
      max2p = pc + c -> r;
      if((max2p > min1p) && (max1p > min2p))
      { // collides on this axis
        double projection_difference = std::min(max2p - min1p, max1p - min2p);
        if(i == 0)
        {
          *offset = projection_difference;
          *axis = axi[i];
        }
        if(*offset > projection_difference)
        {
          *offset = projection_difference;
          *axis = axi[i];
        }
      }
      else
      { // no collision on this axis
        return false;
      }
    }
    return !_eq(*offset, 0);
  }
  return false; // no collision or undefined collision
}
