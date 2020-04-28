#include "controller/slicer.h"
#include "model/floater.h"
#include "model/solid.h"
#include "model/collider/circle.h"
#include "misc_utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

slicer_t slicer;

void slicer_t::tick(obj *o)
{
  if(!enabled)
  {
    return;
  }
  if(o -> layer == 0)
  {
    tick_sea(static_cast<sea *>(o));
  }
  if(o -> layer == 1)
  {
    tick_floater(static_cast<floater *>(o));
  }
  if(o -> layer == 2)
  {
    tick_solid(static_cast<solid *>(o));
  }
  if(o -> layer == 3)
  {
    tick_attachment(static_cast<attachment *>(o));
  }
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
      tick(it.second);
    }
  }
}

void slicer_t::tick_sea(sea *o)
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
        glm::dmat3 transform = glm::dmat3(1);
                   transform = glm::translate(transform, origin -> pp.position);
                   transform = glm::translate(transform, {-origin -> grid.x / 2, -origin -> grid.z / 2});
                   transform = glm::rotate(transform, origin -> pp.angle);
        for(int i = 0; i < op.size(); i++)
        {
          glm::dvec3 transformed = transform * glm::dvec3(op[i], 1);
          op[i] = {transformed.x, transformed.y};
        }
        std::vector<glm::dvec2> tp = origin -> get_bounding_perimeter();
        transform = glm::dmat3(1);
        transform = glm::translate(transform, target -> pp.position);
        transform = glm::translate(transform, {-target -> grid.x / 2, -target -> grid.z / 2});
        transform = glm::rotate(transform, target -> pp.angle);
        for(int i = 0; i < tp.size(); i++)
        {
          glm::dvec3 transformed = transform * glm::dvec3(tp[i], 1);
          tp[i] = {transformed.x, transformed.y};
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
}

void slicer_t::tick_floater(floater *o)
{
  if(o -> targeted)
  {
    glm::dvec2 forward_axis = get_rotation_matrix(o -> pp.angle) * glm::dvec2(0, 1);
    o -> pp.position_velocity += target_f_acc * forward_axis;
    o -> pp.angular_velocity -= target_r_acc;
    o -> pp.tilt_velocity -= target_f_acc * glm::dvec2(1, 0);// + target_r_acc * glm::dvec2(0, 1);
  }
  tick_physical_properties(o -> pp);
}

void slicer_t::tick_solid(solid *o)
{
  tick_physical_properties(o -> pp);
}

void slicer_t::tick_attachment(attachment *o)
{
  tick_physical_properties(o -> pp);
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
