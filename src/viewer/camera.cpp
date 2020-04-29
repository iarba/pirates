#include "viewer/camera.h"

camera_t::camera_t(scppr::scppr *renderer)
{
  this -> renderer = renderer;
  this -> position = {0, 0};
  this -> acceleration = {0, 0};
}

camera_t::~camera_t()
{
}

void camera_t::update()
{
  position += acceleration;
  glm::dvec3 position_3d = {position.x, 10, position.y};
  renderer -> set_camera(0, position_3d, 0, 0, 0, scppr::SCPPR_CAMERA_EYE); 
}

void camera_t::accelerate(glm::dvec2 direction)
{
  acceleration += direction;
}

void camera_t::set_position(glm::dvec2 position)
{
  this -> position = position;
}
