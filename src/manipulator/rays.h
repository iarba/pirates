#ifndef MANIPULATOR_RAYS_H
#define MANIPULATOR_RAYS_H

#include "viewer/camera.h"

class ray
{
public:
  ray(camera_t *camera, glm::dvec2 pos1, glm::dvec2 pos2, int button);
  glm::dvec2 tl_position; // top left position
  glm::dvec2 br_position; // bottom right position
  glm::dvec2 position; // position on release
  int button;
  bool consumed = false;
};

#endif // MANIPULATOR_RAYS_H
