#include "viewer/viewer.h"
#include "viewer/alias.h"
#include "viewer/floater.h"

manipulator_t *viewer_t::init(std::string path, sea *s)
{
  this -> path = path;
  renderer = new scppr::scppr("Pirates", path + "scppr/assets/");
  cube = new scppr::model_t(path + "scppr/assets/cube.obj");
  dirt.diffuse = new scppr::texture_t(path + "assets/dirt.jpg");
  grass.diffuse = new scppr::texture_t(path + "assets/grass.jpg");
  stone.diffuse = new scppr::texture_t(path + "assets/stone.jpg");
  wood.diffuse = new scppr::texture_t(path + "assets/wood.jpg");
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
  floater_viewer *fv = (floater_viewer *)alias.get(f);
  if(fv == NULL)
  {
    fv = new floater_viewer(f, cube);
    alias.put(f, fv);
  }
  fv -> update(renderer, f);
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
