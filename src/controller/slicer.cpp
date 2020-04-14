#include "controller/slicer.h"
#include "model/floater.h"
#include "model/solid.h"

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
  for(auto it : o -> children)
  {
    tick(it.second);
  }
}

void slicer_t::tick_sea(sea *o)
{
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
