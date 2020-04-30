#include "model/physical_properties.h"
#include "misc_utils.h"

physical_properties::physical_properties()
{
}

physical_properties::physical_properties(boost::property_tree::ptree node)
{
  position = tree_to_vec2(node.get_child("position"));
  position_velocity = tree_to_vec2(node.get_child("position_velocity"));
  angle = node.get<double>("angle");
  angular_velocity = node.get<double>("angular_velocity");
  tilt = tree_to_vec2(node.get_child("tilt"));
  tilt_velocity = tree_to_vec2(node.get_child("tilt_velocity"));
  mass = node.get<double>("mass");
  inverse_mass = node.get<double>("inverse_mass");
}

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

physical_properties operator+(const physical_properties &pp1, const physical_properties &pp2)
{
  physical_properties res = pp1;
  glm::dmat2 rmat = get_rotation_matrix(pp1.angle);
  res.position += rmat * pp2.position;
  res.position_velocity += rmat * pp2.position;
  res.angle += pp2.angle;
  res.angular_velocity += pp2.angular_velocity;
  res.tilt += pp2.tilt;
  res.tilt_velocity += pp2.tilt_velocity;
  res.mass += pp2.mass;
  if(_eq(pp1.inverse_mass, 0) || _eq(pp2.inverse_mass, 0))
  {
    res.inverse_mass = 0;
  }
  else
  {
    res.inverse_mass = 1.0 / (1.0 / pp1.inverse_mass + 1.0 / pp2.inverse_mass);
  }
  return res;
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
