#include "test/collision.h"
#include "test/suite.h"
#include "model/collider/circle.h"
#include "model/collider/box.h"
#include "misc_utils.h"

void test_collision()
{
  physical_properties pp1, pp2;
  glm::dvec2 axis;
  double offset;
  TEST("TESTING CIRLCE CIRCLE COLLISION FAR");
  pp1.position = {0, 0};
  pp2.position = {10, -2};
  collider_circle c1(pp1, 2);
  collider_circle c2(pp2, 3);
  if(c1.collides(&c2, &axis, &offset))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
  TEST("TESTING CIRLCE CIRCLE COLLISION TOUCHING X");
  pp1.position = {0, 0};
  pp2.position = {5, 0};
  c1 = collider_circle(pp1, 2);
  c2 = collider_circle(pp2, 3);
  if(c1.collides(&c2, &axis, &offset))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
  TEST("TESTING CIRLCE CIRCLE COLLISION TOUCHING Y");
  pp1.position = {0, 0};
  pp2.position = {0, 5};
  c1 = collider_circle(pp1, 2);
  c2 = collider_circle(pp2, 3);
  if(c1.collides(&c2, &axis, &offset))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
  TEST("TESTING CIRLCE CIRCLE COLLISION TOUCHING DIAGONAL");
  pp1.position = {0, 0};
  pp2.position = {-3, -4};
  c1 = collider_circle(pp1, 2);
  c2 = collider_circle(pp2, 3);
  if(c1.collides(&c2, &axis, &offset))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
  TEST("TESTING CIRLCE CIRCLE COLLISION INTERSECTING");
  pp1.position = {0, 0};
  pp2.position = {3.5, 0};
  c1 = collider_circle(pp1, 2);
  c2 = collider_circle(pp2, 3);
  if(c1.collides(&c2, &axis, &offset) && _eq(axis, {1, 0}) && _eq(offset, 1.5))
  {
    PASS;
  }
  else
  {
    FAIL;
  }
  TEST("TESTING CIRLCE CIRCLE COLLISION NESTED");
  pp1.position = {0, 0};
  pp2.position = {-1.5, 0};
  c1 = collider_circle(pp1, 2);
  c2 = collider_circle(pp2, 3);
  if(c1.collides(&c2, &axis, &offset) && _eq(axis, {-1, 0}) && _eq(offset, 3.5))
  {
    PASS;
  }
  else
  {
    FAIL;
  }
  TEST("TESTING CIRLCE CIRCLE COLLISION NESTED");
  pp1.position = {0, 0};
  pp2.position = {0, 0};
  c1 = collider_circle(pp1, 2);
  c2 = collider_circle(pp2, 3);
  if(c1.collides(&c2, &axis, &offset) && _eq(offset, 5))
  {
    PASS;
  }
  else
  {
    std::string reason = "expected offset to be 5, got " + std::to_string(offset);
    FAIL_REASON(reason);
  }
}
