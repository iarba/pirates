#ifndef MANIPULATOR_MANIPULATOR_H
#define MANIPULATOR_MANIPULATOR_H

#include "viewer/camera.h"
#include "model/sea.h"
#include <scppr.h>

class manipulator_t
{
public:
  manipulator_t(sea *s, camera_t *camera, scppr::scppr *renderer);
  ~manipulator_t();
  void poll();
  void keyboard_callback(int key, int scancode, int action, int mods);
private:
  sea *s;
  camera_t *camera;
  scppr::scppr *renderer;
};

#endif
