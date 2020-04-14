#include "model/physical_properties.h"

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
