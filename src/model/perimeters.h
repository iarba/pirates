#ifndef MODEL_PERIMETERS_H
#define MODEL_PERIMETERS_H

#include <glm/glm.hpp>
#include <vector>

class perimeters_t
{
public:
  std::vector<std::vector<glm::dvec2>> perimeters;
  void clear();
  void add(std::vector<glm::dvec2> partial_perimeter);
  friend perimeters_t operator+(const perimeters_t &p1, const perimeters_t &p2);
};

#endif // MODEL_PERIMETERS_H
