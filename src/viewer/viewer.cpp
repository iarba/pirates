#include "viewer/viewer.h"

void viewer_t::init(std::string path)
{
  this -> path = path;
  renderer = new scppr::scppr("Pirates", path);
}

void viewer_t::destroy()
{
  delete renderer;
}

void viewer_t::draw(sea *s)
{
  renderer -> poll();
  renderer -> draw();
}

bool viewer_t::is_open()
{
  return renderer -> is_open();
}

viewer_t viewer;
