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

// directional bottom left x
std::map<direction_t, double> dblx = boost::assign::map_list_of
(up, 0.5)
(down, -0.5)
(left, 0.5)
(right, -0.5);

// directional bottom left z
std::map<direction_t, double> dblz = boost::assign::map_list_of
(up, -0.5)
(down, 0.5)
(left, 0.5)
(right, -0.5);


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

cell_t::cell_t()
{
}

cell_t::cell_t(boost::property_tree::ptree node)
{
  passable = node.get<bool>("passable");
  solid = node.get<bool>("solid");
  collidable = node.get<bool>("collidable");
  material = static_cast<floater_material_t>(node.get<int>("material"));
}

boost::property_tree::ptree cell_t::serialise()
{
  boost::property_tree::ptree node;
  node.put("passable", passable);
  node.put("solid", solid);
  node.put("collidable", collidable);
  node.put("material", static_cast<int> (material));
  return node;
}

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

grid_t::grid_t(boost::property_tree::ptree node)
{
  x = node.get<int>("x");
  z = node.get<int>("z");
  _grid = new cell_t*[x];
  for(int i = 0; i < x; i++)
  {
    _grid[i] = new cell_t[z];
    for(int j = 0; j < z; j++)
    {
      _grid[i][j] = cell_t(node.get_child(std::to_string(i) + "." + std::to_string(j)));
    }
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

boost::property_tree::ptree grid_t::serialise()
{
  boost::property_tree::ptree node;
  node.put("x", x);
  node.put("z", x);
  for(int i = 0; i < x; i++)
  {
    for(int j = 0; j < z; j++)
    {
      node.put_child(std::to_string(i) + "." + std::to_string(j), at(i, j) -> serialise());
    }
  }
  return node;
}

floater::floater(namer_t floater_namer, int x, int z):obj(1, floater_namer), grid(x, z)
{
}

floater::floater(boost::property_tree::ptree node):obj(node), grid(node.get_child("grid")), pp(node.get_child("pp"))
{
  targeted = node.get<bool>("targeted");
}

floater::~floater()
{
}

collider_box floater::get_bounding_box()
{
  // -2 because the border is water guaranteed
  double x = (grid.x - 2) * CELL_SIZE;
  double z = (grid.z - 2) * CELL_SIZE;
  return collider_box(pp, x, z);
}

void floater::generate_perimeter()
{
  bounding_perimeter.clear();
  marker++;
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
  int startx = x;
  int startz = z;
  while(!(x == startx && z == startz && d == up))
  { // while we're not where we started
    if(grid.at(x + dblx[d], z + dblz[d]) -> mark != marker)
    {
      bounding_perimeter.push_back({x + dblx[d], z + dblz[d]});
      grid.at(x + dblx[d], z + dblz[d]) -> mark = marker;
    }
    if(grid.at(x + ddx[dlo[d]], z + ddz[dlo[d]]) -> collidable)
    { // left is collidable now, move there and add to perimeter
      d = dlo[d];
      x += ddx[d];
      z += ddz[d];
      continue;
    }
    if(grid.at(x + ddx[d], z + ddz[d]) -> collidable)
    { // forward is collidable
      x += ddx[d];
      z += ddz[d];
      continue;
    }
    // if we got here, that means there's uncollidable both to our left and forward, so we turn right
    d = dro[d];
  }
  if(grid.at(x + dblx[d], z + dblz[d]) -> mark != marker)
  {
    bounding_perimeter.push_back({x + dblx[d], z + dblz[d]});
    grid.at(x + dblx[d], z + dblz[d]) -> mark = marker;
  }
  perimeter_expired = false;
}

std::vector<glm::dvec2> floater::get_bounding_perimeter()
{
  if(this -> perimeter_expired)
  {
    this -> generate_perimeter();
  }
  return bounding_perimeter;
}

boost::property_tree::ptree floater::serialise()
{
  boost::property_tree::ptree node = obj::serialise();
  node.put_child("pp", pp.serialise());
  node.put_child("grid", grid.serialise());
  node.put("targeted", targeted);
  return node;
}
