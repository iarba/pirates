#include "test/suite.h"
#include "log.h"
#include "test/collision.h"
#include "test/floater.h"
#include "test/utils.h"

int failures;
int tests;

int execute_test()
{
  log_test();
  test_collision();
  test_floater();
  test_utils();
  printf("PASSED %d/%d TESTS!\n", tests - failures, tests);
  return failures;
}
