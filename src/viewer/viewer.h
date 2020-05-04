#ifndef VIEWER_VIEWER_H
#define VIEWER_VIEWER_H

#include <scppr.h>
#include "model/obj.h"
#include "model/sea.h"
#include "model/floater.h"
#include "model/solid.h"
#include "model/pirate.h"
#include "model/structure.h"
#include "model/attachment.h"
#include "model/physical_properties.h"
#include "viewer/camera.h"
#include "manipulator/manipulator.h"

class viewer_t
{
public:
  manipulator_t *init(std::string path, sea *s);
  void destroy();
  void draw(obj *o);
  bool is_open();
private:
  void _draw(obj *o, physical_properties pp);
  void draw_sea(sea *s, physical_properties pp);
  void draw_floater(floater *f, physical_properties pp);
  void draw_solid(solid *s, physical_properties pp);
  void draw_attachment(attachment *a, physical_properties pp);
  scppr::model_t *cube;
  scppr::model_t *cannon;
  scppr::scppr *renderer;
  std::string path;
  camera_t *camera;
  std::map<floater_material_t, scppr::material_t> floater_material_vector;
  std::map<pirate_race_t, scppr::material_t> pirate_material_vector;
  scppr::material_t highlight_material;
  scppr::light_t *sun;
};

extern viewer_t viewer;

#endif // VIEWER_VIEWER_H
