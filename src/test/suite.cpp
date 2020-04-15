#include "test/suite.h"
#include "log.h"
#include "test/collision.h"

int failures;
int tests;

int execute_test()
{
  log_test();
  test_collision();
  printf("PASSED %d/%d TESTS!\n", tests - failures, tests);
  return failures;
}
