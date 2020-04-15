#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <cstdio>
#include <string>

#define TEST(x) printf(x " - ");fflush(stdin);tests++;
#define PASS printf("PASSED\n");
#define FAIL printf("FAILED\n");failures++;
#define FAIL_REASON(x) printf("FAILED\n%s\n", x.c_str());failures++;

extern int failures;
extern int tests;

int execute_test();

#endif // TEST_SUITE_H
