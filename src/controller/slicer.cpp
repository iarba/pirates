#include "controller/slicer.h"
#include "model/floater.h"
#include "model/solid.h"
#include "controller/utils.h"

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
      glm::dvec2 axis;
      double offset;
      collider_box obb = origin -> get_bounding_box();
      collider_box tbb = target -> get_bounding_box();
      if(obb.collides(&tbb, &axis, &offset))
      {
        // get perimeter of both shapes
        std::vector<glm::dvec2> op = origin -> get_bounding_perimeter();
        std::vector<glm::dvec2> tp = origin -> get_bounding_perimeter();
        // get pruned vector of points, filtering by points that are in the target bounding box
        std::vector<glm::dvec2> pop;
        std::vector<glm::dvec2> ptp;
        // iterate both list of points
        for(auto point:pop)
        {
          if(point_is_in_shape(point, tp))
          { // find 1 point that is contained within the perimeter of the other floater
            // determine the edge within the other floater that is closest to the point
            get_edge_closest_to_point(point, tp, &axis, &offset);
            // the projection between the point and the edge is the separation requirement
          }
        }
      }
    }
  }
}

void slicer_t::tick_floater(floater *o)
{
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
