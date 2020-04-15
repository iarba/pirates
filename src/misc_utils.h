#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>

bool _eq(double a, double b);

bool _eq(glm::dvec2 a, glm::dvec2 b);

glm::mat2x2 get_rotation_matrix(double angle);

#endif // UTILS_H

