#include "test/solid.h"
#include "test/suite.h"
#include "model/floater.h"
#include "model/pirate.h"
#include "model/structure.h"
#include "misc_utils.h"
#include "model/sea.h"
#include "controller/slicer.h"

void test_solid_collision()
{
  solid *s1 = new pirate();
  solid *s2 = new pirate();
  s2 -> pp.position = {1, 1};
  floater *f = new floater(-1, 5, 5);
  f -> children[1] = s1;
  f -> children[2] = s2;
  sea *s = new sea();
  s -> children[1] = f;
  TEST("TESTING SOLIDS STAYING STILL");
  slicer.tick(s);
  if(!_eq(s1 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "solid 1 moved";
    FAIL_REASON(reason);
    goto next1;
  }
  if(!_eq(s2 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "solid 2 moved";
    FAIL_REASON(reason);
    goto next1;
  }
  PASS;
  next1:
  TEST("TESTING SOLIDS COLLISION");
  s2 -> pp.position = {0.5, 0.3};
  slicer.tick(s);
  if(_eq(s1 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "solid 1 didn't move";
    FAIL_REASON(reason);
    goto next2;
  }
  if(_eq(s2 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "solid 2 didn't move";
    FAIL_REASON(reason);
    goto next2;
  }
  PASS;
  next2:
  delete s;
  s1 = new structure();
  s2 = new pirate();
  s2 -> pp.position = {1, 1};
  f = new floater(-1, 5, 5);
  f -> children[1] = s1;
  f -> children[2] = s2;
  s = new sea();
  s -> children[1] = f;
  TEST("TESTING STRUCTURE STAYING STILL");
  slicer.tick(s);
  if(!_eq(s1 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "solid 1 moved";
    FAIL_REASON(reason);
    goto next3;
  }
  if(!_eq(s2 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "solid 2 moved";
    FAIL_REASON(reason);
    goto next3;
  }
  PASS;
  next3:
  TEST("TESTING STRUCTURE COLLISION");
  s2 -> pp.position = {0.5, 0.3};
  slicer.tick(s);
  if(!_eq(s1 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "structure moved";
    FAIL_REASON(reason);
    goto next4;
  }
  if(_eq(s2 -> pp.position_velocity, {0, 0}))
  {
    std::string reason = "solid 2 didn't move";
    FAIL_REASON(reason);
    goto next4;
  }
  PASS;
  next4:
  delete s;
}

void test_solid()
{
  test_solid_collision();
}
