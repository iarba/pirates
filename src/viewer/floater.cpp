#include "viewer/floater.h"
#include "misc_utils.h"

floater_viewer::floater_viewer(floater *f, scppr::model_t *cube)
{
  this -> x = f -> grid.x;
  this -> z = f -> grid.z;
  grid = new scppr::object_t **[x];
  for(int i = 0; i < x; i++)
  {
    grid[i] = new scppr::object_t *[z]();
  }
  this -> cube = cube;
}

floater_viewer::~floater_viewer()
{
  for(int i = 0; i < x; i++)
  {
    delete[] grid[i];
  }
  delete[] grid;
}

void floater_viewer::update(scppr::scppr *renderer, floater *f)
{
  glm::dvec2 translation = {f -> pp.position.x, f -> pp.position.y};
  glm::dmat2 rotation = get_rotation_matrix(f -> pp.angle);
  for(int i = 0; i < x; i++)
  {
    for(int j = 0; j < z; j++)
    {
      auto c = f -> grid.at(i, j);
      if(c -> collidable)
      {
        if(grid[i][j] == NULL)
        {
          grid[i][j] = new scppr::object_t();
          grid[i][j] -> model = cube;
          grid[i][j] -> scale = {0.5, 0.5, 0.5};
          renderer -> add_object(grid[i][j]);
        }
        glm::dvec2 pos = {i - x / 2, j - z / 2};
        pos = rotation * pos;
        pos = pos + translation;
        grid[i][j] -> position = {pos.x, 0, pos.y};
        grid[i][j] -> rotation = {0, f -> pp.angle, 0};
      }
    }
  }
}
