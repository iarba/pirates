#ifndef CONTROLLER_UTILS_H
#define CONTROLLER_UTILS_H

#include <glm/glm.hpp>
#include <vector>

bool point_is_in_shape(glm::dvec2 point, std::vector<glm::dvec2> shape);

glm::dvec2 get_edge_closest_to_point(glm::dvec2 point, std::vector<glm::dvec2> shape, glm::dvec2 *axis, double *offset);

#endif // CONTROLLER_UTILS_H
