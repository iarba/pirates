#include "viewer/viewer.h"
#include "viewer/alias.h"
#include "viewer/floater.h"
#include "model/highlight.h"
#include "model/target_indicator.h"

#define SIMPLE_ID 1
#define FLOATER_ID 2

manipulator_t *viewer_t::init(std::string path)
{
  this -> path = path;
  renderer = new scppr::scppr("Pirates", path + "scppr/assets/");
  cube = new scppr::model_t(path + "scppr/assets/cube.obj");
  cannon = new scppr::model_t(path + "assets/cannon.obj");
  scppr::material_t dirt, grass, sand, stone, wood, neko;
  dirt.diffuse = new scppr::texture_t(path + "assets/dirt.jpg");
  grass.diffuse = new scppr::texture_t(path + "assets/grass.jpg");
  sand.diffuse = new scppr::texture_t(path + "assets/sand.jpg");
  stone.diffuse = new scppr::texture_t(path + "assets/stone.jpg");
  wood.diffuse = new scppr::texture_t(path + "assets/wood.jpg");
  neko.diffuse = new scppr::texture_t(path + "assets/neko.png");
  highlight_material.diffuse = new scppr::texture_t(path + "assets/highlight.png");
  target_indicator_material.diffuse = new scppr::texture_t(path + "assets/target_indicator.png");
  pirate_material_vector[pirate_neko] = neko;
  camera = new camera_t(renderer);
  sun = new scppr::light_t();
  sun -> color = {0.5, 0.5, 0.5};
  sun -> position = {0, 1000, 0};
  renderer -> add_light(sun);
  return new manipulator_t(camera, renderer);
}

void viewer_t::destroy()
{
  delete camera;
  delete sun;
  for( auto it : pirate_material_vector)
  {
    delete it.second.diffuse;
  }
  delete cube;
  delete cannon;
  delete renderer;
}

void viewer_t::draw(obj *o)
{
  alias.clean();
  camera -> update();
  _draw(o, physical_properties());
  std::map<void *, aliased_t> clean = alias.get_clean();
  for(auto it : clean)
  {
    alias.remove(it.first);
    if(it.second.identifier == SIMPLE_ID)
    {
      scppr::object_t *o = (scppr::object_t *)it.second.what;
      renderer -> remove_object(o);
      delete o;
    }
    if(it.second.identifier == FLOATER_ID)
    {
      floater_viewer *fv = (floater_viewer *)it.second.what;
      fv -> unload(renderer);
      delete fv;
    }
  }
  renderer -> draw();
}

void viewer_t::_draw(obj *o, physical_properties pp)
{
  if(o -> layer == 0)
  {
    draw_sea(static_cast<sea *>(o), pp);
  }
  if(o -> layer == 1)
  {
    draw_floater(static_cast<floater *>(o), pp);
  }
  if(o -> layer == 2)
  {
    draw_solid(static_cast<solid *>(o), pp);
  }
  if(o -> layer == 3)
  {
    draw_attachment(static_cast<attachment *>(o), pp);
  }
}

void viewer_t::draw_sea(sea *s, physical_properties pp)
{
  auto cc = s -> children;
  for(auto it : cc)
  {
    _draw(it.second, pp);
  }
}

void viewer_t::draw_floater(floater *f, physical_properties pp)
{
  physical_properties abs_pp = pp + f -> pp;
  if(f -> focused)
  {
    camera -> set_position(abs_pp.position);
  }
  floater_viewer *fv = (floater_viewer *)alias.get(f);
  if(fv == NULL)
  {
    fv = new floater_viewer(f, cube);
    alias.put(f, fv, FLOATER_ID);
  }
  fv -> update(renderer, f);
  auto cc = f -> children;
  for(auto it : cc)
  {
    _draw(it.second, abs_pp);
  }
}

void viewer_t::draw_solid(solid *s, physical_properties pp)
{
  physical_properties abs_pp = pp + s -> pp;
  if(s -> focused)
  {
    camera -> set_position(abs_pp.position);
  }
  if(s -> name == pirate_namer)
  {
    pirate *p = static_cast<pirate *>(s);
    scppr::object_t *pv = (scppr::object_t *)alias.get(p);
    if(pv == NULL)
    {
      pv = new scppr::object_t();
      pv -> model = cube;
      pv -> scale = {0.50, 0.01, 0.50};
      pv -> rotation = {0, M_PI / 2, 0};
      pv -> material_overwrite[0] = pirate_material_vector[p -> race];
      renderer -> add_object(pv);
      alias.put(p, pv, SIMPLE_ID);
    }
    abs_pp.angle = 0;
    pv -> position = {abs_pp.position.x, 0.51, abs_pp.position.y};
  }
  if(s -> name == structure_namer)
  {
    structure *st = static_cast<structure *>(s);
    scppr::object_t *stv = (scppr::object_t *)alias.get(st);
    if(stv == NULL)
    {
      stv = new scppr::object_t();
      stv -> model = cannon;
      stv -> scale = {0.50, 0.50, 0.50};
      renderer -> add_object(stv);
      alias.put(st, stv, SIMPLE_ID);
    }
    stv -> position = {abs_pp.position.x, 1, abs_pp.position.y};
    stv -> rotation = {0, abs_pp.angle, 0};
  }
  auto cc = s -> children;
  for(auto it : cc)
  {
    _draw(it.second, abs_pp);
  }
}

void viewer_t::draw_attachment(attachment *a, physical_properties pp)
{
  physical_properties abs_pp = pp + a -> pp;
  if(a -> name == highlight_namer)
  {
    highlight *hl = static_cast<highlight *>(a);
    scppr::object_t *hlv = (scppr::object_t *)alias.get(hl);
    if(hlv == NULL)
    {
      hlv = new scppr::object_t();
      hlv -> model = cube;
      hlv -> scale = {0.50, 0.01, 0.50};
      hlv -> material_overwrite[0] = highlight_material;
      renderer -> add_object(hlv);
      alias.put(hl, hlv, SIMPLE_ID);
    }
    hlv -> position = {abs_pp.position.x, 0.53, abs_pp.position.y};
    hlv -> rotation = {0, abs_pp.angle, 0};
  }
  if(a -> name == target_indicator_namer)
  {
    target_indicator *ti = static_cast<target_indicator *>(a);
    scppr::object_t *tiv = (scppr::object_t *)alias.get(ti);
    if(tiv == NULL)
    {
      tiv = new scppr::object_t();
      tiv -> model = cube;
      tiv -> scale = {0.50, 0.01, 0.50};
      tiv -> material_overwrite[0] = target_indicator_material;
      renderer -> add_object(tiv);
      alias.put(ti, tiv, SIMPLE_ID);
    }
    tiv -> position = {abs_pp.position.x, 0.53, abs_pp.position.y};
    tiv -> rotation = {0, abs_pp.angle, 0};
  }
  auto cc = a -> children;
  for(auto it : cc)
  {
    _draw(it.second, abs_pp);
  }
}

bool viewer_t::is_open()
{
  return renderer -> is_open();
}

viewer_t viewer;
