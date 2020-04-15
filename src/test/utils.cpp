#include "test/utils.h"
#include "test/suite.h"
#include "controller/utils.h"

void test_point_in_shape()
{
  glm::dvec2 point = {0, 0};
  std::vector<glm::dvec2> shape;
  TEST("TESTING EMPTY SHAPE");
  if(point_is_in_shape(point, shape))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
  TEST("TESTING 1 POINT SHAPE");
  shape.push_back({-1, -1});
  if(point_is_in_shape(point, shape))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
  TEST("TESTING 2 POINT SHAPE");
  shape.push_back({-1, 2});
  if(point_is_in_shape(point, shape))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
  TEST("TESTING 3 POINT SHAPE IN");
  shape.push_back({1, -1});
  if(point_is_in_shape(point, shape))
  {
    PASS;
  }
  else
  {
    FAIL;
  }
  TEST("TESTING 3 POINT SHAPE OUT");
  point = {4, 0};
  if(point_is_in_shape(point, shape))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
  TEST("TESTING RECTANGLE OUT");
  shape.push_back({1, 2});
  if(point_is_in_shape(point, shape))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
  TEST("TESTING RECTANGLE IN");
  point = {-0.5, 1};
  if(point_is_in_shape(point, shape))
  {
    PASS;
  }
  else
  {
    FAIL;
  }
  TEST("TESTING CONCAVE 1");
  shape.clear();
  shape.push_back({0, 0});
  shape.push_back({1, 0});
  shape.push_back({1, 1});
  shape.push_back({2, 1});
  shape.push_back({2, 0});
  shape.push_back({3, 0});
  shape.push_back({3, 2});
  shape.push_back({0, 2});
  point = {0.5, 0.5};
  if(point_is_in_shape(point, shape))
  {
    PASS;
  }
  else
  {
    FAIL;
  }
  TEST("TESTING CONCAVE 2");
  point = {0.5, 1};
  if(point_is_in_shape(point, shape))
  {
    PASS;
  }
  else
  {
    FAIL;
  }
  TEST("TESTING CONCAVE 3");
  point = {-0.5, 0.5};
  if(point_is_in_shape(point, shape))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
  TEST("TESTING CONCAVE 4");
  point = {1.5, 0.5};
  if(point_is_in_shape(point, shape))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
  TEST("TESTING CONCAVE 3");
  point = {3.5, 0.5};
  if(point_is_in_shape(point, shape))
  {
    FAIL;
  }
  else
  {
    PASS;
  }
}

void test_utils()
{
  test_point_in_shape();
}
