#ifndef VIEWER_CAMERA_H
#define VIEWER_CAMERA_H

#include <scppr.h>

class camera_t
{
public:
  camera_t(scppr::scppr *renderer);
  ~camera_t();
  void update();
  void accelerate(glm::dvec2 direction);
  void set_position(glm::dvec2 position);
  glm::dvec2 position;
  glm::dvec2 acceleration;
  scppr::scppr *renderer;
  double height = 10;
  double fov = M_PI / 2;
  glm::dvec2 viewport = {800, 800};
};

#endif // VIEWER_CAMERA_H
