#include "viewer/viewer.h"


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

void viewer_t::draw(sea *s)
{
  // update the camera
  camera -> update();

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
