#include "manipulator/manipulator.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include "controller/slicer.h"
#include "manipulator/rays.h"

void keyboard_callback_wrapper(void *data_point, int key, int scancode, int action, int mods)
{
  manipulator_t *man = (manipulator_t *)data_point;
  man -> keyboard_callback(key, scancode, action, mods);
}

void mouse_callback_wrapper(void *data_point, double xpos, double ypos)
{
  manipulator_t *man = (manipulator_t *)data_point;
  man -> mouse_callback(xpos, ypos);
}

void click_callback_wrapper(void *data_point, int button, int state, int mods)
{
  manipulator_t *man = (manipulator_t *)data_point;
  man -> click_callback(button, state, mods);
}

manipulator_t::manipulator_t(camera_t *camera, scppr::scppr *renderer)
{
  this -> camera = camera;
  this -> renderer = renderer;
  renderer -> add_listener(scppr::keyboard_listener, (void *)&keyboard_callback_wrapper, (void *)this);
  renderer -> add_listener(scppr::mouse_listener, (void *)&mouse_callback_wrapper, (void *)this);
  renderer -> add_listener(scppr::click_listener, (void *)&click_callback_wrapper, (void *)this);
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
      slicer.targeted_forward_enable();
    }
    if(key == GLFW_KEY_A)
    {
      slicer.targeted_turn_left_enable();
    }
    if(key == GLFW_KEY_S)
    {
    }
    if(key == GLFW_KEY_D)
    {
      slicer.targeted_turn_right_enable();
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
      slicer.targeted_forward_disable();
    }
    if(key == GLFW_KEY_A)
    {
      slicer.targeted_turn_left_disable();
    }
    if(key == GLFW_KEY_S)
    {
    }
    if(key == GLFW_KEY_D)
    {
      slicer.targeted_turn_right_disable();
    }
    if(key == GLFW_KEY_B)
    {
      slicer.toggle_board();
    }
  }
}

void manipulator_t::mouse_callback(double xpos, double ypos)
{
  this -> cursor_x = xpos;
  this -> cursor_y = ypos;
}

void manipulator_t::click_callback(int button, int state, int mods)
{
  if(state == GLFW_RELEASE)
  {
    slicer.add_ray(ray(camera, cursor_x, cursor_y, button));
  }
}
