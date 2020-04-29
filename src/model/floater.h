#ifndef MODEL_FLOATER_H
#define MODEL_FLOATER_H

#include "model/obj.h"
#include "model/physical_properties.h"
#include "model/collider/box.h"
#include <vector>

#define CELL_SIZE 1

enum floater_material_t
{
  floater_dirt = 1,
  floater_grass,
  floater_sand,
  floater_stone,
  floater_wood
};

class cell_t
{
public:
  cell_t();
  cell_t(boost::property_tree::ptree node);
  boost::property_tree::ptree serialise();
  bool full = false;
  bool passable = false;
  bool solid = false;
  bool collidable = false;
  int mark = 0;
  floater_material_t material = floater_wood;
};

class grid_t
{
public:
  grid_t(int x, int z);
  grid_t(boost::property_tree::ptree node);
  ~grid_t();
  cell_t *at(int x, int z);
  boost::property_tree::ptree serialise();
  cell_t **_grid;
  int x;
  int z;
};

class floater : public obj
{
public:
  floater(namer_t floater_namer, int x, int z);
  floater(boost::property_tree::ptree node);
  ~floater();
  collider_box get_bounding_box();
  void generate_perimeter();
  std::vector<glm::dvec2> get_bounding_perimeter();
  virtual boost::property_tree::ptree serialise();
  physical_properties pp;
  grid_t grid;
  bool targeted = false;
  // V not serialised V
  std::vector<glm::dvec2> bounding_perimeter;
  int marker = 0;
  bool perimeter_expired = true;
};

#endif // MODEL_FLOATER_H
