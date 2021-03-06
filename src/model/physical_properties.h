#ifndef MODEL_PHYSICAL_PROPERTIES_H
#define MODEL_PHYSICAL_PROPERTIES_H

#include <glm/glm.hpp>
#include <boost/property_tree/ptree.hpp>

class physical_properties
{
public:
  physical_properties();
  physical_properties(boost::property_tree::ptree node);
  glm::dvec2 offset = {0, 0};
  glm::dvec2 position = {0, 0};
  glm::dvec2 position_velocity = {0, 0};
  double angle = 0;
  double angular_velocity = 0;
  glm::dvec2 tilt = {0, 0};
  glm::dvec2 tilt_velocity = {0, 0};
  double mass = 1;
  double inverse_mass = 1;
  boost::property_tree::ptree serialise();
  friend physical_properties operator+(const physical_properties &pp1, const physical_properties &pp2);
};


class pp_builder
{
  pp_builder();
  pp_builder &at(glm::dvec2 pos);
  pp_builder &moving(glm::dvec2 vel);
  pp_builder &rotated(double a);
  pp_builder &rotating(double av);
  pp_builder &tilted(glm::dvec2 tilt);
  pp_builder &tilting(glm::dvec2 tilt_velocity);
  pp_builder &weighting(double m);
  physical_properties build();
  physical_properties pp;
};

#endif // MODEL_PHYSICAL_PROPERTIES_H
