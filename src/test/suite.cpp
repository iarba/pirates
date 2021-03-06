#include "test/suite.h"
#include "log.h"
#include "test/collision.h"
#include "test/floater.h"
#include "test/utils.h"
#include "test/serialisation.h"
#include "test/solid.h"

int failures;
int tests;

int execute_test()
{
  log_test();
  test_collision();
  test_floater();
  test_utils();
  test_serialisation();
  test_solid();
  printf("PASSED %d/%d TESTS!\n", tests - failures, tests);
  return failures;
}
