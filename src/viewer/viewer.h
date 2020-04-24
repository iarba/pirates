#ifndef VIEWER_VIEWER_H
#define VIEWER_VIEWER_H

#include <scppr.h>
#include "model/sea.h"
#include "viewer/camera.h"
#include "manipulator/manipulator.h"

class viewer_t
{
public:
  manipulator_t *init(std::string path, sea *s);
  void destroy();
  void draw(sea *s);
  bool is_open();
private:
  scppr::model_t *cube;
  scppr::scppr *renderer;
  std::string path;
  camera_t *camera;
};

extern viewer_t viewer;

#endif // VIEWER_VIEWER_H
