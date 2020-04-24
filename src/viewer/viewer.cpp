#include "viewer/viewer.h"
#include "viewer/alias.h"

manipulator_t *viewer_t::init(std::string path, sea *s)
{
  this -> path = path;
  renderer = new scppr::scppr("Pirates", path);
  cube = new scppr::model_t(path + "cube.obj");
  camera = new camera_t(renderer);
  return new manipulator_t(s, camera, renderer);
}

void viewer_t::destroy()
{
  delete camera;
  delete renderer;
}

void viewer_t::draw(obj *o)
{
  camera -> update();
  _draw(o, physical_properties());
  renderer -> draw();
}

void viewer_t::_draw(obj *o, physical_properties pp)
{
  if(o -> layer == 0)
  {
    draw_sea(static_cast<sea *>(o), pp);
  }
  if(o -> layer == 1)
  {
    draw_floater(static_cast<floater *>(o), pp);
  }
  if(o -> layer == 2)
  {
    draw_solid(static_cast<solid *>(o), pp);
  }
  if(o -> layer == 3)
  {
    draw_attachment(static_cast<attachment *>(o), pp);
  }
  auto cc = o -> children;
  for(auto it : cc)
  {
    _draw(it.second, pp);
  }
}

void viewer_t::draw_sea(sea *s, physical_properties pp)
{
}

void viewer_t::draw_floater(floater *f, physical_properties pp)
{
  scppr::object_t *o = (scppr::object_t *)alias.get(f);
  if(o == NULL)
  {
    o = new scppr::object_t();
    o -> model = cube;
    o -> scale = {1.5, 0.5, 1.5};
    alias.put(f, o);
    renderer -> add_object(o);
  }
  o -> position = {f -> pp.position.x + pp.position.x, 0, f -> pp.position.y + pp.position.y};
  o -> rotation = {f -> pp.tilt.x + pp.tilt.x, f -> pp.angle + pp.angle, f -> pp.tilt.y + pp.tilt.y};
}

void viewer_t::draw_solid(solid *s, physical_properties pp)
{
}

void viewer_t::draw_attachment(attachment *a, physical_properties pp)
{
}

bool viewer_t::is_open()
{
  return renderer -> is_open();
}

viewer_t viewer;
