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
private:
  void tick_children_of(obj *o);
  void tick_sea(sea *o);
  void tick_floater(floater *o);
  void tick_solid(solid *o);
  void tick_attachment(attachment *o);
  void tick_physical_properties(physical_properties &pp);
  double target_f_acc = 0;
  double target_r_acc = 0;
  std::vector<ray> rays;
};

extern slicer_t slicer;

#endif // CONTROLLER_SLICER_H
