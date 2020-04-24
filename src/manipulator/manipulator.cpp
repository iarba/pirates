#include "manipulator/manipulator.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include "controller/slicer.h"

void keyboard_callback_wrapper(void *data_point, int key, int scancode, int action, int mods)
{
  manipulator_t *man = (manipulator_t *)data_point;
  man -> keyboard_callback(key, scancode, action, mods);
}

manipulator_t::manipulator_t(sea *s, camera_t *camera, scppr::scppr *renderer)
{
  this -> s = s;
  this -> camera = camera;
  this -> renderer = renderer;
  renderer -> add_listener(scppr::keyboard_listener, (void *)&keyboard_callback_wrapper, (void *)this);
}

manipulator_t::~manipulator_t()
{
  renderer -> remove_listener(scppr::keyboard_listener);
}

void manipulator_t::poll()
{
  renderer -> poll();
}

void manipulator_t::keyboard_callback(int key, int scancode, int action, int mods)
{
  if(action == GLFW_PRESS)
  {
    if(key == GLFW_KEY_W)
    {
      camera -> accelerate({1, 0});
    }
    if(key == GLFW_KEY_A)
    {
      camera -> accelerate({0, -1});
    }
    if(key == GLFW_KEY_S)
    {
      camera -> accelerate({-1, 0});
    }
    if(key == GLFW_KEY_D)
    {
      camera -> accelerate({0, 1});
    }
    if(key == GLFW_KEY_SPACE)
    {
      slicer.tick(s);
    }
  }
  if(action == GLFW_RELEASE)
  {
    if(key == GLFW_KEY_W)
    {
      camera -> accelerate({-1, 0});
    }
    if(key == GLFW_KEY_A)
    {
      camera -> accelerate({0, 1});
    }
    if(key == GLFW_KEY_S)
    {
      camera -> accelerate({1, 0});
    }
    if(key == GLFW_KEY_D)
    {
      camera -> accelerate({0, -1});
    }
  }
}
