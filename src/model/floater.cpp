#include "model/floater.h"
#include "model/collider/box.h"

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
  return collider_box(&(this -> pp), x/2, z/2);
}
