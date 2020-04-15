#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <cstdio>

#define TEST(x) printf(x " - ");fflush(stdin);tests++;
#define PASS printf("PASSED\n");
#define FAIL printf("FAILED\n");failures++;

extern int failures;
extern int tests;

int execute_test();

#endif // TEST_SUITE_H
