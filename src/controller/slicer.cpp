#include "controller/slicer.h"
#include "model/floater.h"
#include "model/solid.h"
#include "model/collider/circle.h"
#include "model/pirate.h"
#include "model/structure.h"
#include "misc_utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

slicer_t slicer;

void slicer_t::tick_children_of(obj *o, physical_properties pp)
{
  auto cc = o -> children;
  for(auto it : cc)
  {
    o -> lifespan -= dt;
    if((-10 < o -> lifespan) && (o -> lifespan < 0))
    {
      o -> expired = true;
    }
    if(o -> expired)
    {
      delete it.second;
      o -> children.erase(it.first);
    }
    else
    {
      _tick(it.second, pp);
    }
  }
}

void slicer_t::tick(obj *o)
{
  if(!enabled)
  {
    return;
  }
  _tick(o, physical_properties());
}

void slicer_t::_tick(obj *o, physical_properties pp)
{
  if(o -> layer == 0)
  {
    tick_sea(static_cast<sea *>(o), pp);
  }
  if(o -> layer == 1)
  {
    tick_floater(static_cast<floater *>(o), pp);
  }
  if(o -> layer == 2)
  {
    tick_solid(static_cast<solid *>(o), pp);
  }
  if(o -> layer == 3)
  {
    tick_attachment(static_cast<attachment *>(o), pp);
  }
}

void slicer_t::tick_sea(sea *o, physical_properties pp)
{
  // for every floater, check collision against every other floater in sight
  // pls don't add too many floaters at once, otherwise this will get expensive
  for(auto oit : o -> children)
  {
    floater *origin = static_cast<floater *>(oit.second);
    for(auto tit : o -> children)
    {
      // prune most collisions with a bounding box check
      floater *target = static_cast<floater *>(tit.second);
      if(origin == target)
      { // yes pointer equality
        continue;
      }
      glm::dvec2 axis;
      double offset;
      collider_box obb = origin -> get_bounding_box();
      collider_box tbb = target -> get_bounding_box();
      if(obb.collides(&tbb, &axis, &offset))
      {
        // get perimeter of both shapes
        std::vector<glm::dvec2> op = origin -> get_bounding_perimeter();
        glm::dvec2 translation = origin -> pp.position;
        glm::dmat2 rotation = get_rotation_matrix(origin -> pp.angle);
        for(int i = 0; i < op.size(); i++)
        {
          op[i] = translation + rotation * (op[i] - glm::dvec2(origin -> grid.x / 2, origin -> grid.z / 2));
        }
        std::vector<glm::dvec2> tp = target -> get_bounding_perimeter();
        translation = target -> pp.position;
        rotation = get_rotation_matrix(target -> pp.angle);
        for(int i = 0; i < tp.size(); i++)
        {
          tp[i] = translation + rotation * (tp[i] - glm::dvec2(target -> grid.x / 2, target -> grid.z / 2));
        }
        // get pruned vector of points, filtering by points that are in the target bounding box
        std::vector<glm::dvec2> pop;
        std::vector<glm::dvec2> ptp;
        physical_properties point_pp;
        for(auto point : op)
        {
          point_pp.position = point;
          collider_box point_collider(point_pp, 0.1, 0.1);
          if(point_collider.collides(&tbb, &axis, &offset))
          {
            pop.push_back(point);
          }
        }
        for(auto point : tp)
        {
          point_pp.position = point;
          collider_box point_collider(point_pp, 0.1, 0.1);
          if(point_collider.collides(&obb, &axis, &offset))
          {
            ptp.push_back(point);
          }
        }
        // iterate both list of points
        for(auto point:pop)
        {
          // find 1 point that is contained within the perimeter of the other floater
          if(point_is_in_shape(point, tp))
          {
            // determine the edge within the other floater that is closest to the point
            get_edge_closest_to_point(point, tp, &axis, &offset);
            // the projection between the point and the edge is the separation requirement
            glm::dvec2 impulse = axis * offset;
            double mass = origin -> pp.mass + target -> pp.mass;
            // push the origin
            glm::dvec2 push_axis = glm::normalize(point - origin -> pp.position);
            glm::dvec2 push_delta = glm::dot(impulse, push_axis) * push_axis;
            origin -> pp.position_velocity += push_delta * floater_collision_push_strength * mass * origin -> pp.inverse_mass;
            // rotate the origin
            glm::dvec2 torque_axis = get_rotation_matrix(M_PI / 2) * push_axis;
            double torque_delta = glm::dot(impulse, torque_axis);
            origin -> pp.angular_velocity += torque_delta * floater_collision_torque_strength * mass * origin -> pp.inverse_mass;
            // tilt the origin
            origin -> pp.tilt_velocity += push_delta * floater_collision_tilt_strength * mass * origin -> pp.inverse_mass;
            // invert the impulse
            impulse = -impulse;
            // push the target
            push_axis = glm::normalize(point - target -> pp.position);
            push_delta = glm::dot(impulse, push_axis) * push_axis;
            target -> pp.position_velocity += push_delta * floater_collision_push_strength * mass * target -> pp.inverse_mass;
            // rotate the target
            torque_axis = get_rotation_matrix(M_PI / 2) * push_axis;
            torque_delta = glm::dot(impulse, torque_axis);
            target -> pp.angular_velocity += torque_delta * floater_collision_torque_strength * mass * target -> pp.inverse_mass;
            // tilt the target
            target -> pp.tilt_velocity += push_delta * floater_collision_tilt_strength * mass * target -> pp.inverse_mass;
          }
        }
        // iterate both list of points
        for(auto point:ptp)
        {
          // find 1 point that is contained within the perimeter of the other floater
          if(point_is_in_shape(point, op))
          {
            // determine the edge within the other floater that is closest to the point
            get_edge_closest_to_point(point, op, &axis, &offset);
            // the projection between the point and the edge is the separation requirement
            glm::dvec2 impulse = axis * offset;
            double mass = target -> pp.mass + origin -> pp.mass;
            // push the target
            glm::dvec2 push_axis = glm::normalize(point - target -> pp.position);
            glm::dvec2 push_delta = glm::dot(impulse, push_axis) * push_axis;
            target -> pp.position_velocity += push_delta * floater_collision_push_strength * mass * target -> pp.inverse_mass;
            // rotate the target
            glm::dvec2 torque_axis = get_rotation_matrix(M_PI / 2) * push_axis;
            double torque_delta = glm::dot(impulse, torque_axis);
            target -> pp.angular_velocity += torque_delta * floater_collision_torque_strength * mass * target -> pp.inverse_mass;
            // tilt the target
            target -> pp.tilt_velocity += push_delta * floater_collision_tilt_strength * mass * target -> pp.inverse_mass;
            // invert the impulse
            impulse = -impulse;
            // push the origin
            push_axis = glm::normalize(point - origin -> pp.position);
            push_delta = glm::dot(impulse, push_axis) * push_axis;
            origin -> pp.position_velocity += push_delta * floater_collision_push_strength * mass * origin -> pp.inverse_mass;
            // rotate the origin
            torque_axis = get_rotation_matrix(M_PI / 2) * push_axis;
            torque_delta = glm::dot(impulse, torque_axis);
            origin -> pp.angular_velocity += torque_delta * floater_collision_torque_strength * mass * origin -> pp.inverse_mass;
            // tilt the origin
            origin -> pp.tilt_velocity += push_delta * floater_collision_tilt_strength * mass * origin -> pp.inverse_mass;
          }
        }
      }
    }
  }
  tick_children_of(o, pp);
  rays.clear();
}

void slicer_t::tick_floater(floater *o, physical_properties pp)
{
  if(o -> targeted)
  {
    glm::dvec2 forward_axis = get_rotation_matrix(o -> pp.angle) * glm::dvec2(0, 1);
    o -> pp.position_velocity += target_f_acc * forward_axis;
    o -> pp.angular_velocity -= target_r_acc;
    o -> pp.tilt_velocity -= target_f_acc * glm::dvec2(1, 0);// + target_r_acc * glm::dvec2(0, 1);
  }
  tick_physical_properties(o -> pp);
  for(auto oit : o -> children)
  {
    if(oit.second -> name != pirate_namer)
    { // pointless
      continue;
    }
    pirate *origin = static_cast<pirate *>(oit.second);
    for(auto tit : o -> children)
    {
      if(origin == tit.second)
      { // yes pointer equality
        continue;
      }
      if(tit.second -> name == pirate_namer)
      {
        pirate *target = static_cast<pirate *>(tit.second);
        glm::dvec2 axis;
        double offset;
        collider_circle oc = origin -> get_collider();
        collider_circle tc = target -> get_collider();
        if(oc.collides(&tc, &axis, &offset))
        {
          glm::dvec2 impulse = axis * offset;
          double mass = origin -> pp.mass + target -> pp.mass;
          // push the origin
          origin -> pp.position_velocity += impulse * solid_collision_push_strength * mass * origin -> pp.inverse_mass;
          // invert the impulse
          impulse = -impulse;
          // push the target
          target -> pp.position_velocity += impulse * solid_collision_push_strength * mass * target -> pp.inverse_mass;
        }
      }
      if(tit.second -> name == structure_namer)
      {
        structure *target = static_cast<structure *>(tit.second);
        glm::dvec2 axis;
        double offset;
        collider_circle oc = origin -> get_collider();
        collider_box tc = target -> get_collider();
        if(oc.collides(&tc, &axis, &offset))
        {
          glm::dvec2 impulse = axis * offset;
          double mass = origin -> pp.mass + target -> pp.mass;
          // push the origin
          origin -> pp.position_velocity += impulse * solid_collision_push_strength * mass * origin -> pp.inverse_mass;
        }
      }
    }
  }
  tick_children_of(o, pp + o -> pp);
}

void slicer_t::tick_solid(solid *o, physical_properties pp)
{
  physical_properties abs_pp = pp + o -> pp;
  for(auto ray : rays)
  {
    if(ray.button == GLFW_MOUSE_BUTTON_1)
    {
      o -> targeted = glm::distance(ray.position, abs_pp.position) < 0.5;
      o -> focused = glm::distance(ray.position, abs_pp.position) < 0.5;
    }
    if(ray.button == GLFW_MOUSE_BUTTON_2)
    {
      if(o -> targeted)
      {
        // move target to new position
      }
    }
  }
  tick_physical_properties(o -> pp);
  tick_children_of(o, abs_pp);
}

void slicer_t::tick_attachment(attachment *o, physical_properties pp)
{
  tick_physical_properties(o -> pp);
  tick_children_of(o, pp);
}

void slicer_t::tick_physical_properties(physical_properties &pp)
{
  // tilt tends towards {0, 0}, the further away it is the more velocity it will gain towards it
  pp.tilt_velocity     -= pp.tilt * tilt_acceleration;

  pp.position_velocity *= position_velocity_decay;
  pp.angular_velocity  *= angular_velocity_decay;
  pp.tilt_velocity     *= tilt_velocity_decay;

  pp.position          += pp.position_velocity * dt;
  pp.angle             += pp.angular_velocity * dt;
  pp.tilt              += pp.tilt_velocity * dt;
  double mass = 1;
}

void slicer_t::targeted_forward_enable()
{
  target_f_acc += 1;
}

void slicer_t::targeted_forward_disable()
{
  target_f_acc -= 1;
}

void slicer_t::targeted_turn_right_enable()
{
  target_r_acc += 1;
}

void slicer_t::targeted_turn_right_disable()
{
  target_r_acc -= 1;
}

void slicer_t::targeted_turn_left_enable()
{
  target_r_acc -= 1;
}

void slicer_t::targeted_turn_left_disable()
{
  target_r_acc += 1;
}

void slicer_t::add_ray(ray r)
{
  rays.push_back(r);
}
