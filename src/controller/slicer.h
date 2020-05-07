#ifndef CONTROLLER_SLICER_H
#define CONTROLLER_SLICER_H

#include "model/obj.h"
#include "model/sea.h"
#include "model/floater.h"
#include "model/solid.h"
#include "model/attachment.h"
#include "model/physical_properties.h"
#include "manipulator/rays.h"

class slicer_t
{
public:
  void tick(obj *o);
  void targeted_forward_enable();
  void targeted_forward_disable();
  void targeted_turn_right_enable();
  void targeted_turn_right_disable();
  void targeted_turn_left_enable();
  void targeted_turn_left_disable();
  void add_ray(ray r);
  bool enabled = true;
  double sps = 100;
  double dt = 0.01;
  double tilt_acceleration = 1;
  double position_velocity_decay = 0.9;
  double angular_velocity_decay = 0.9;
  double tilt_velocity_decay = 0.9;
  double floater_collision_push_strength = 1;
  double floater_collision_torque_strength = 1;
  double floater_collision_tilt_strength = 1;
  double solid_collision_push_strength = 1;
  double solid_speed = 0.4;
private:
  void _tick(obj *o, physical_properties pp);
  void tick_children_of(obj *o, physical_properties pp);
  void tick_sea(sea *o, physical_properties pp);
  void tick_floater(floater *o, physical_properties pp);
  void tick_solid(solid *o, physical_properties pp);
  void tick_attachment(attachment *o, physical_properties pp);
  void tick_physical_properties(physical_properties &pp);
  double target_f_acc = 0;
  double target_r_acc = 0;
  int occupation = 0;
  std::vector<ray> rays;
  solid *selected;
  floater *ray_targeted;
  glm::dvec2 pos_targeted;
};

extern slicer_t slicer;

#endif // CONTROLLER_SLICER_H
