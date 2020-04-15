#include "test/suite.h"
#include "log.h"

int failures;
int tests;

int execute_test()
{
  log_test();
  printf("PASSED %d/%d TESTS!\n", tests - failures, tests);
  return failures;
}
