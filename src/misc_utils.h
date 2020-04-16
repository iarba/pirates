#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include <vector>

bool _eq(double a, double b);

bool _eq(glm::dvec2 a, glm::dvec2 b);

glm::dmat2x2 get_rotation_matrix(double angle);

bool point_is_in_shape(glm::dvec2 point, std::vector<glm::dvec2> shape);

glm::dvec2 get_edge_closest_to_point(glm::dvec2 point, std::vector<glm::dvec2> shape, glm::dvec2 *axis, double *offset);

#endif // UTILS_H

