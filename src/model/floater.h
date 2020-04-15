#ifndef MODEL_FLOATER_H
#define MODEL_FLOATER_H

#include "model/obj.h"
#include "model/physical_properties.h"
#include "model/collider/box.h"
#include <vector>

#define CELL_SIZE 1

class cell_t
{
public:
  bool full = false;
  bool passable = false;
  bool solid = false;
  bool collidable = false;
};

class grid_t
{
public:
  grid_t(int x, int z);
  ~grid_t();
  cell_t *at(int x, int z);
  cell_t **_grid;
  int x;
  int z;
};

class floater : public obj
{
public:
  floater(namer_t floater_namer, int x, int z);
  ~floater();
  collider_box get_bounding_box();
  void generate_perimeter();
  std::vector<glm::dvec2> get_bounding_perimeter();
  std::vector<glm::dvec2> bounding_perimeter;
  bool perimeter_expired = true;
  physical_properties pp;
  grid_t grid;
};

#endif // MODEL_FLOATER_H
