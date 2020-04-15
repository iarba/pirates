#include "controller/utils.h"

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
