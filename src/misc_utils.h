#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include <vector>
#include <boost/property_tree/ptree.hpp>

bool _eq(double a, double b);

bool _eq(glm::dvec2 a, glm::dvec2 b);

glm::dmat2x2 get_rotation_matrix(double angle);

bool point_is_in_shape(glm::dvec2 point, std::vector<glm::dvec2> shape);

glm::dvec2 get_edge_closest_to_point(glm::dvec2 point, std::vector<glm::dvec2> shape, glm::dvec2 *axis, double *offset);

boost::property_tree::ptree vec2_to_tree(glm::dvec2 input);

boost::property_tree::ptree vec3_to_tree(glm::dvec3 input);

glm::dvec2 tree_to_vec2(boost::property_tree::ptree input);

glm::dvec3 tree_to_vec3(boost::property_tree::ptree input);

#endif // UTILS_H
