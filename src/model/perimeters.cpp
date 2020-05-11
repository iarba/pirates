#include "model/perimeters.h"

void perimeters_t::clear()
{
  perimeters.clear();
}

void perimeters_t::add(std::vector<glm::dvec2> partial_perimeter)
{
  perimeters.push_back(partial_perimeter);
}

perimeters_t operator+(const perimeters_t &p1, const perimeters_t &p2)
{
  perimeters_t res = p1;
  for(auto perimeter : p2.perimeters)
  {
    res.perimeters.push_back(perimeter);
  }
  return res;
}
