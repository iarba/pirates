#ifndef VIEWER_FLOATER_H
#define VIEWER_FLOATER_H

#endif // VIEWER_FLOATER_H
#include <scppr.h>
#include "model/floater.h"
#include <map>

class floater_viewer
{
public:
  floater_viewer(floater *f, scppr::model_t *cube);
  ~floater_viewer();
  void unload(scppr::scppr *renderer);
  void update(scppr::scppr *renderer, floater *f);
private:
  scppr::object_t ***grid;
  int x;
  int z;
  scppr::model_t *cube;
};
