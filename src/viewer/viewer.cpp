#include "viewer/viewer.h"
#include "viewer/alias.h"
#include "viewer/floater.h"
#include "model/highlight.h"
#include "model/target_indicator.h"
#include "loader.h"

#define SIMPLE_ID 1
#define FLOATER_ID 2

manipulator_t *viewer_t::init(std::string path)
{
  this -> path = path;
  renderer = new scppr::scppr("Pirates", path + "scppr/assets/");
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
    fv = new floater_viewer(f);
    alias.put(f, fv, FLOATER_ID);
  }
  fv -> update(renderer, f, abs_pp);
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
      renderer -> add_object(pv);
      alias.put(p, pv, SIMPLE_ID);
    }
    abs_pp.angle = 0;
    loader::name_registry.apply_loader(p -> race, pv);
    pv -> position += glm::dvec3(abs_pp.position.x, 0, abs_pp.position.y);
  }
  if(s -> name == structure_namer)
  {
    structure *st = static_cast<structure *>(s);
    scppr::object_t *stv = (scppr::object_t *)alias.get(st);
    if(stv == NULL)
    {
      stv = new scppr::object_t();
      renderer -> add_object(stv);
      alias.put(st, stv, SIMPLE_ID);
    }
    loader::name_registry.apply_loader(st -> type, stv);
    stv -> position += glm::dvec3(abs_pp.position.x, 0, abs_pp.position.y);
    stv -> rotation += glm::dvec3(0, abs_pp.angle, 0);
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
  scppr::object_t *av = (scppr::object_t *)alias.get(a);
  if(av == NULL)
  {
    av = new scppr::object_t();
    renderer -> add_object(av);
    alias.put(a, av, SIMPLE_ID);
  }
  loader::name_registry.apply_loader(a -> name, av);
  av -> position += glm::dvec3(abs_pp.position.x, 0, abs_pp.position.y);
  av -> rotation += glm::dvec3(0, abs_pp.angle, 0);
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
