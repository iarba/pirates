#include "viewer/viewer.h"

void viewer_t::init(std::string path)
{
  this -> path = path;
  renderer = new scppr::scppr("Pirates", path);
  cube = new scppr::model_t(path + "cube.obj");
}

void viewer_t::destroy()
{
  delete renderer;
}

void viewer_t::draw(sea *s)
{
  renderer -> poll();
  scppr::object_t *obj = new scppr::object_t();
  obj -> model = cube;
  renderer -> add_object(obj);
  renderer -> draw();
  renderer -> remove_object(obj);
  delete obj;
}

bool viewer_t::is_open()
{
  return renderer -> is_open();
}

viewer_t viewer;
