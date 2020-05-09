#ifndef MANIPULATOR_RAYS_H
#define MANIPULATOR_RAYS_H

#include "viewer/camera.h"

class ray
{
public:
  ray(camera_t *camera, double x, double y, int button);
  glm::dvec2 position;
  int button;
  bool consumed = false;
};

#endif // MANIPULATOR_RAYS_H
