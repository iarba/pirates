#include "model/floater.h"
#include "model/collider/box.h"
#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include <map>
#include "loader.h"
#include "misc_utils.h"

floater_material_t floater_default_material;

void floater::init(boost::property_tree::ptree namer_node)
{
  boost::property_tree::ptree node = namer_node.get_child("base.material");
  for(auto mat:node)
  {
    namer_t namer = mat.second.get<namer_t>("namer");
    try
    {
      if(mat.second.get<bool>("default"))
      {
        floater_default_material = namer;
      }
    }
    catch(std::exception &e)
    {
    }
    loader::name_registry.bind(namer, mat.second.get<std::string>("name"));
    glm::dvec3 position = tree_to_vec3(mat.second.get_child("model_offset.position"));
    glm::dvec3 rotation = tree_to_vec3(mat.second.get_child("model_offset.rotation"));
    glm::dvec3 scale = tree_to_vec3(mat.second.get_child("model_offset.scale"));
    scppr::model_t *model = loader::name_registry.get_model(mat.second.get<std::string>("model"));
    std::map<int, scppr::material_t> texture_overload;
    boost::property_tree::ptree t_node = mat.second.get_child("texture");
    for(auto tex : t_node)
    {
      texture_overload[std::stoi(tex.first)] = loader::name_registry.get_texture(tex.second.get<std::string>(""));
    }
    loader::name_registry.bind_loader(namer, boost::bind(handy_loader, _1, position, rotation, scale, model, texture_overload));
  }
}

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
  material = floater_default_material;
}

cell_t::cell_t(boost::property_tree::ptree node)
{
  passable = node.get<bool>("passable");
  solid = node.get<bool>("solid");
  collidable = node.get<bool>("collidable");
  material = node.get<floater_material_t>("material");
}

boost::property_tree::ptree cell_t::serialise()
{
  boost::property_tree::ptree node;
  node.put("passable", passable);
  node.put("solid", solid);
  node.put("collidable", collidable);
  node.put("material", material);
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

void grid_t::fill_parse_mark(int xpos, int zpos, int marker)
{
  if(!at(xpos, zpos) -> collidable)
  {
    return;
  }
  if(at(xpos, zpos) -> perimeter_parsed_mark == marker)
  {
    return;
  }
  at(xpos, zpos) -> perimeter_parsed_mark = marker;
  fill_parse_mark(xpos + 1, zpos    , marker);
  fill_parse_mark(xpos - 1, zpos    , marker);
  fill_parse_mark(xpos    , zpos + 1, marker);
  fill_parse_mark(xpos    , zpos - 1, marker);
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
  while(true)
  {
    std::vector<glm::dvec2> partial_perimeter;
    for(x = 0; x < grid.x; x++)
    {
      for(z = 0; z < grid.z; z++)
      {
        if(grid.at(x, z) -> collidable && grid.at(x, z) -> perimeter_visited_mark != marker)
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
      break;
    }
    // step 2 - travel around the border, always keeping uncollidable to your left
    // assumption - grid edge is uncollidable
    direction_t d = right; // we know up and left is uncollidable
    int startx = x;
    int startz = z;
    while(!(x == startx && z == startz && d == up))
    { // while we're not where we started
      if(grid.at(x + dblx[d], z + dblz[d]) -> perimeter_parsed_mark != marker)
      {
        partial_perimeter.push_back({x + dblx[d], z + dblz[d]});
        grid.at(x + dblx[d], z + dblz[d]) -> perimeter_parsed_mark = marker;
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
    if(grid.at(x + dblx[d], z + dblz[d]) -> perimeter_parsed_mark != marker)
    {
      partial_perimeter.push_back({x + dblx[d], z + dblz[d]});
      grid.at(x + dblx[d], z + dblz[d]) -> perimeter_parsed_mark = marker;
    }
    grid.fill_parse_mark(x, z, marker);
    bounding_perimeter.add(partial_perimeter);
  }
  perimeter_expired = false;
}

glm::dvec2 generate_centroid_for(std::vector<glm::dvec2> bounding_perimeter, double *area)
{
  glm::dvec2 centroid;
  *area = 0;
  int j = bounding_perimeter.size() - 1;
  for(int i = 0; i < bounding_perimeter.size(); i++)
  {
    double part = bounding_perimeter[i].x * bounding_perimeter[j].y - bounding_perimeter[j].x * bounding_perimeter[i].y;
    *area += part;
    centroid.x += (bounding_perimeter[i].x + bounding_perimeter[j].x) * part;
    centroid.y += (bounding_perimeter[i].y + bounding_perimeter[j].y) * part;
    j = i;
  }
  centroid.x = centroid.x / (3 * *area);
  centroid.y = centroid.y / (3 * *area);
  *area /= 2;
  return centroid;
}
void floater::generate_centroid()
{
  if(this -> perimeter_expired)
  {
    this -> generate_perimeter();
  }
  std::vector<glm::dvec2> partial_centroids;
  std::vector<double> partial_areas;
  for(int i = 0; i < bounding_perimeter.perimeters.size(); i++)
  {
    double partial_area = 0;
    glm::dvec2 partial_centroid = generate_centroid_for(bounding_perimeter.perimeters[i], &partial_area);
    partial_centroids.push_back(partial_centroid);
    partial_areas.push_back(partial_area);
  }
  double total_area = 0;
  for(int i = 0; i < bounding_perimeter.perimeters.size(); i++)
  {
    centroid += partial_areas[i] * partial_centroids[i];
    total_area += partial_areas[i];
  }
  centroid /= total_area;
  pp.offset = centroid - glm::dvec2((double)(grid.x - 1) / 2, (double)(grid.z - 1) / 2);
  centroid_expired = false;
}

perimeters_t floater::get_bounding_perimeter()
{
  if(this -> perimeter_expired)
  {
    this -> generate_perimeter();
  }
  if(this -> centroid_expired)
  {
    this -> generate_centroid();
  }
  perimeters_t perimeter = bounding_perimeter;
  for(auto it : children)
  {
    obj *child = it.second;
    if(child -> layer == 1)
    {
      perimeter = perimeter + static_cast<floater *>(child) -> get_bounding_perimeter();
    }
  }
  glm::dvec2 translation = pp.position;
  glm::dmat2 rotation = get_rotation_matrix(pp.angle);
  for(int i = 0; i < perimeter.perimeters.size(); i++)
  {
    for(int j = 0; j < perimeter.perimeters[i].size(); j++)
    {
      perimeter.perimeters[i][j] = translation + pp.offset + rotation * (perimeter.perimeters[i][j] - glm::dvec2((double)(grid.x - 1) / 2, (double)(grid.z - 1) / 2) - pp.offset);
    }
  }
  return perimeter;
}

glm::dvec2 floater::get_centroid()
{
  if(this -> centroid_expired)
  {
    this -> generate_centroid();
  }
  glm::dvec2 translation = pp.position;
  glm::dvec2 cent = translation + centroid - glm::dvec2((double)(grid.x - 1) / 2, (double)(grid.z - 1) / 2);
  return cent;
}

boost::property_tree::ptree floater::serialise()
{
  boost::property_tree::ptree node = obj::serialise();
  node.put_child("pp", pp.serialise());
  node.put_child("grid", grid.serialise());
  node.put("targeted", targeted);
  return node;
}
