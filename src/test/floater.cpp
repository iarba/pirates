#include "test/floater.h"
#include "test/suite.h"
#include "model/floater.h"
#include "model/collider/box.h"
#include "misc_utils.h"
#include "model/sea.h"
#include "controller/slicer.h"

void test_floater_interaction()
{
  floater *f = new floater(-1, 11, 16);
  f -> grid.at( 2,  2) -> collidable = true;
  f -> grid.at( 2,  3) -> collidable = true;
  f -> grid.at( 2,  4) -> collidable = true;
  f -> grid.at( 2,  5) -> collidable = true;
  f -> grid.at( 2,  9) -> collidable = true;
  f -> grid.at( 2, 10) -> collidable = true;
  f -> grid.at( 2, 11) -> collidable = true;

  f -> grid.at( 3,  4) -> collidable = true;
  f -> grid.at( 3,  5) -> collidable = true;
  f -> grid.at( 3,  7) -> collidable = true;
  f -> grid.at( 3,  9) -> collidable = true;
  f -> grid.at( 3, 11) -> collidable = true;
  f -> grid.at( 3, 12) -> collidable = true;

  f -> grid.at( 4,  4) -> collidable = true;
  f -> grid.at( 4,  5) -> collidable = true;
  f -> grid.at( 4,  6) -> collidable = true;
  f -> grid.at( 4,  7) -> collidable = true;
  f -> grid.at( 4,  8) -> collidable = true;
  f -> grid.at( 4,  9) -> collidable = true;
  f -> grid.at( 4, 11) -> collidable = true;

  f -> grid.at( 5,  4) -> collidable = true;
  f -> grid.at( 5,  5) -> collidable = true;
  f -> grid.at( 5,  6) -> collidable = true;
  f -> grid.at( 5,  7) -> collidable = true;
  f -> grid.at( 5,  8) -> collidable = true;
  f -> grid.at( 5,  9) -> collidable = true;
  f -> grid.at( 5, 10) -> collidable = true;
  f -> grid.at( 5, 11) -> collidable = true;
  f -> grid.at( 5, 12) -> collidable = true;
  f -> grid.at( 5, 13) -> collidable = true;

  f -> grid.at( 6,  4) -> collidable = true;
  f -> grid.at( 6,  5) -> collidable = true;
  f -> grid.at( 6,  6) -> collidable = true;
  f -> grid.at( 6,  7) -> collidable = true;
  f -> grid.at( 6,  8) -> collidable = true;
  f -> grid.at( 6,  9) -> collidable = true;
  f -> grid.at( 6, 10) -> collidable = true;
  f -> grid.at( 6, 12) -> collidable = true;

  f -> grid.at( 7,  3) -> collidable = true;
  f -> grid.at( 7,  4) -> collidable = true;
  f -> grid.at( 7,  5) -> collidable = true;
  f -> grid.at( 7,  6) -> collidable = true;
  f -> grid.at( 7,  7) -> collidable = true;
  f -> grid.at( 7,  8) -> collidable = true;
  f -> grid.at( 7,  9) -> collidable = true;
  f -> grid.at( 7, 10) -> collidable = true;

  f -> grid.at( 8,  4) -> collidable = true;
  f -> grid.at( 8,  5) -> collidable = true;
  f -> grid.at( 8,  6) -> collidable = true;
  f -> grid.at( 8,  7) -> collidable = true;
  f -> grid.at( 8,  8) -> collidable = true;
  f -> grid.at( 8,  9) -> collidable = true;
  f -> grid.at( 8, 10) -> collidable = true;

  f -> grid.at( 9,  7) -> collidable = true;
  f -> grid.at( 9,  8) -> collidable = true;

  /*             111111
   *   0123456789012345
   * 0 ................   
   * 1 ................                              
   * 2 ..xxxx...xxx....                        
   * 3 ....xx.x.x.xx...            
   * 4 ....xxxxxx.x....                        
   * 5 ....xxxxxxxxxx..                         
   * 6 ....xxxxxxx.x...                          
   * 7 ...xxxxxxxx.....                          
   * 8 ....xxxxxxx.....                       
   * 9 .......xx.......                           
   *10 ................                            
   */

  TEST("TESTING CREATION OF BOUNDING BOX");
  collider_box cb = f -> get_bounding_box();
  PASS;
  TEST("TESTING PERIMETER GENERATION");
  std::vector<glm::dvec2> v = f -> get_bounding_perimeter();
  if(v.size() == 52)
  {
    PASS;
  }
  else
  {
    std::string reason = "expected size 52 got " + std::to_string(v.size());
    FAIL_REASON(reason);
  }
  delete f;
}

void test_floater_collision()
{
  floater *f1 = new floater(-1, 5, 5);
  f1 -> grid.at(1, 1) -> collidable = true;
  f1 -> grid.at(1, 2) -> collidable = true;
  f1 -> grid.at(1, 3) -> collidable = true; // this should collide
  f1 -> grid.at(2, 1) -> collidable = true;
  f1 -> grid.at(2, 2) -> collidable = true;
  f1 -> grid.at(2, 3) -> collidable = true;
  f1 -> grid.at(3, 1) -> collidable = true;
  f1 -> grid.at(3, 2) -> collidable = true;
  f1 -> grid.at(3, 3) -> collidable = true;
  floater *f2 = new floater(-1, 5, 5);
  f2 -> grid.at(1, 1) -> collidable = true;
  f2 -> grid.at(1, 2) -> collidable = true;
  f2 -> grid.at(1, 3) -> collidable = true;
  f2 -> grid.at(2, 1) -> collidable = true;
  f2 -> grid.at(2, 2) -> collidable = true;
  f2 -> grid.at(2, 3) -> collidable = true;
  f2 -> grid.at(3, 1) -> collidable = true; // this should collide
  f2 -> grid.at(3, 2) -> collidable = true;
  f2 -> grid.at(3, 3) -> collidable = true;
  sea *s = new sea();
  s -> children[1] = f1;
  s -> children[2] = f2;
  TEST("TESTING SIMPLE FLOATER COLLISION");
  f1 -> pp = physical_properties();
  f2 -> pp = physical_properties();
  f1 -> pp.position = {55, 55};
  f2 -> pp.position = {57.5, 57.5};
  slicer.tick(s);
  if(_eq(f1 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "floater 1 didn't move";
    FAIL_REASON(reason);
    goto next1;
  }
  if(_eq(f2 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "floater 2 didn't move";
    FAIL_REASON(reason);
    goto next1;
  }
  PASS;
  next1:
  TEST("TESTING SIMPLE FLOATER COLLISION");
  f1 -> pp = physical_properties();
  f2 -> pp = physical_properties();
  f1 -> pp.position = {55, 55};
  f2 -> pp.position = {52.5, 57.5};
  slicer.tick(s);
  if(_eq(f1 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "floater 1 didn't move";
    FAIL_REASON(reason);
    goto next2;
  }
  if(_eq(f2 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "floater 2 didn't move";
    FAIL_REASON(reason);
    goto next2;
  }
  PASS;
  next2:
  TEST("TESTING SIMPLE FLOATER COLLISION");
  f1 -> pp = physical_properties();
  f2 -> pp = physical_properties();
  f1 -> pp.position = {55, 55};
  f2 -> pp.position = {57.5, 52.5};
  slicer.tick(s);
  if(_eq(f1 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "floater 1 didn't move";
    FAIL_REASON(reason);
    goto next3;
  }
  if(_eq(f2 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "floater 2 didn't move";
    FAIL_REASON(reason);
    goto next3;
  }
  PASS;
  next3:
  TEST("TESTING SIMPLE FLOATER COLLISION");
  f1 -> pp = physical_properties();
  f2 -> pp = physical_properties();
  f1 -> pp.position = {55, 55};
  f2 -> pp.position = {52.5, 52.5};
  slicer.tick(s);
  if(_eq(f1 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "floater 1 didn't move";
    FAIL_REASON(reason);
    goto next4;
  }
  if(_eq(f2 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "floater 2 didn't move";
    FAIL_REASON(reason);
    goto next4;
  }
  PASS;
  next4:
  delete s;
}

void test_floater()
{
  test_floater_interaction();
  test_floater_collision();
}
