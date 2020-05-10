#include "viewer/floater.h"
#include "misc_utils.h"
#include "loader.h"

floater_viewer::floater_viewer(floater *f)
{
  this -> x = f -> grid.x;
  this -> z = f -> grid.z;
  grid = new scppr::object_t **[x];
  for(int i = 0; i < x; i++)
  {
    grid[i] = new scppr::object_t *[z]();
  }
}

floater_viewer::~floater_viewer()
{
  for(int i = 0; i < x; i++)
  {
    for(int j = 0; j < z; j++)
    {
      if(grid[i][j])
      {
        delete grid[i][j];
      }
    }
    delete[] grid[i];
  }
  delete[] grid;
}

void floater_viewer::unload(scppr::scppr *renderer)
{
  for(int i = 0; i < x; i++)
  {
    for(int j = 0; j < z; j++)
    {
      if(grid[i][j])
      {
        renderer -> remove_object(grid[i][j]);
      }
    }
  }
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
          renderer -> add_object(grid[i][j]);
        }
        loader::name_registry.apply_loader(c -> material, grid[i][j]);
        glm::dvec2 pos = {(double)i - (double)(x - 1) / 2, (double)j - (double)(z - 1) / 2};
        pos = rotation * (pos - f -> pp.offset) + f -> pp.offset;
        pos = pos + translation;
        grid[i][j] -> position += glm::dvec3(pos.x, 0, pos.y);
        grid[i][j] -> rotation += glm::dvec3(0, f -> pp.angle, 0);
      }
      else
      {
        if(grid[i][j])
        {
          renderer -> remove_object(grid[i][j]);
          delete grid[i][j];
          grid[i][j] = NULL;
        }
      }
    }
  }
}
