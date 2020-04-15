#include "test/floater.h"
#include "test/suite.h"
#include "model/floater.h"
#include "model/collider/box.h"
#include "utils.h"

void test_floater()
{
  floater *f = new floater("floater", 3, 8);
  TEST("TESTING CREATION OF BOUNDING BOX");
  collider_box cb = f -> get_bounding_box();
  PASS;
  delete f;
}
