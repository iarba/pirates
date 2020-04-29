#include "model/physical_properties.h"
#include "misc_utils.h"

boost::property_tree::ptree physical_properties::serialise()
{
  boost::property_tree::ptree node;
  node.put_child("position", vec2_to_tree(position));
  node.put_child("position_velocity", vec2_to_tree(position_velocity));
  node.put("angle", angle);
  node.put("angular_velocity", angular_velocity);
  node.put_child("tilt", vec2_to_tree(tilt));
  node.put_child("tilt_velocity", vec2_to_tree(tilt_velocity));
  node.put("mass", mass);
  node.put("inverse_mass", inverse_mass);
  return node;
}

pp_builder::pp_builder()
{
}

pp_builder &pp_builder::at(glm::dvec2 pos)
{
  pp.position = pos;
  return *this;
}

pp_builder &pp_builder::moving(glm::dvec2 vel)
{
  pp.position_velocity = vel;
  return *this;
}

pp_builder &pp_builder::rotated(double a)
{
  pp.angle = a;
  return *this;
}

pp_builder &pp_builder::rotating(double av)
{
  pp.angular_velocity = av;
  return *this;
}

pp_builder &pp_builder::tilted(glm::dvec2 t)
{
  pp.tilt = t;
  return *this;
}

pp_builder &pp_builder::tilting(glm::dvec2 tv)
{
  pp.tilt_velocity = tv;
  return *this;
}

pp_builder &pp_builder::weighting(double m)
{
  pp.mass = m;
  return *this;
}

physical_properties pp_builder::build()
{
  return pp;
}
