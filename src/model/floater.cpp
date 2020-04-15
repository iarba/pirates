#include "model/floater.h"

grid_t::grid_t(int x, int z)
{
  this -> x = x;
  this -> z = z;
  _grid = new cell_t*[x];
  for(int i = 0; i < x; i++)
  {
    _grid[x] = new cell_t[z];
  }
}

grid_t::~grid_t()
{
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
