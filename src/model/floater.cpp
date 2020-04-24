#include "model/floater.h"
#include "model/collider/box.h"
#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include <map>

enum direction_t
{
  up,
  down,
  left,
  right
};

// directional delta x
std::map<direction_t, int> ddx = boost::assign::map_list_of
(up, -1)
(down, 1)
(left, 0)
(right, 0);

// directional delta z
std::map<direction_t, int> ddz = boost::assign::map_list_of
(up, 0)
(down, 0)
(left, -1)
(right, 1);

// directional right of
std::map<direction_t, direction_t> dro = boost::assign::map_list_of
(up, right)
(down, left)
(left, up)
(right, down);

// directional left of
std::map<direction_t, direction_t> dlo = boost::assign::map_list_of
(up, left)
(down, right)
(left, down)
(right, up);

grid_t::grid_t(int x, int z)
{
  this -> x = x;
  this -> z = z;
  _grid = new cell_t*[x];
  for(int i = 0; i < x; i++)
  {
    _grid[i] = new cell_t[z];
  }
}

grid_t::~grid_t()
{
  for(int i = 0; i < x; i++)
  {
    delete[] _grid[i];
  }
  delete[] _grid;
}

cell_t *grid_t::at(int x, int z)
{
  return _grid[x] + z;
}

floater::floater(namer_t floater_namer, int x, int z):obj(1, floater_namer), grid(x, z)
{
}

floater::~floater()
{
}

collider_box floater::get_bounding_box()
{
  double x = grid.x * CELL_SIZE;
  double z = grid.z * CELL_SIZE;
  return collider_box(this -> pp, x, z);
}

void floater::generate_perimeter()
{
  bounding_perimeter.clear();
  // step 1 - find first collidable = true
  int x, z;
  bool found = false;
  for(x = 0; x < grid.x; x++)
  {
    for(z = 0; z < grid.z; z++)
    {
      if(grid.at(x, z) -> collidable)
      {
        found = true;
        break;
      }
    }
    if(found)
    {
      break;
    }
  }
  if(!found)
  {
    return;
  }
  // step 2 - travel around the border, always keeping uncollidable to your left
  // assumption - grid edge is uncollidable
  direction_t d = right; // we know up and left is uncollidable
  bounding_perimeter.push_back({x, z});
  while(!(x == bounding_perimeter[0].x && z == bounding_perimeter[0].y && d == up))
  { // while we're not where we started
    if(grid.at(x + ddx[dlo[d]], z + ddz[dlo[d]]) -> collidable)
    { // left is collidable now, move there and add to perimeter
      d = dlo[d];
      x += ddx[d];
      z += ddz[d];
      bounding_perimeter.push_back({x, z});
      continue;
    }
    if(grid.at(x + ddx[d], z + ddz[d]) -> collidable)
    { // forward is collidable
      x += ddx[d];
      z += ddz[d];
      bounding_perimeter.push_back({x, z});
      continue;
    }
    // if we got here, that means there's uncollidable both to our left and forward, so we turn right
    d = dro[d];
  }
}

std::vector<glm::dvec2> floater::get_bounding_perimeter()
{
  if(this -> perimeter_expired)
  {
    this -> generate_perimeter();
  }
  return bounding_perimeter;
}
