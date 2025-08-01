#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int tests_run;
extern int tests_failed;
extern int current_test_failures;

#define ASSERT(test, message) do { \
    tests_run++; \
    if (!(test)) { \
        printf("FAIL: %s - %s (line %d)\n", __func__, message, __LINE__); \
        tests_failed++; \
        current_test_failures++; \
    } \
} while(0)

#define ASSERT_EQ(expected, actual, message) do { \
    tests_run++; \
    if ((expected) != (actual)) { \
        printf("FAIL: %s - %s: expected %d, got %d (line %d)\n", \
               __func__, message, (int)(expected), (int)(actual), __LINE__); \
        tests_failed++; \
        current_test_failures++; \
    } \
} while(0)

#define ASSERT_EQ_HEX(expected, actual, message) do { \
    tests_run++; \
    if ((expected) != (actual)) { \
        printf("FAIL: %s - %s: expected 0x%02X, got 0x%02X (line %d)\n", \
               __func__, message, (unsigned)(expected), (unsigned)(actual), __LINE__); \
        tests_failed++; \
        current_test_failures++; \
    } \
} while(0)

#define ASSERT_CRITICAL(test, message) do { \
    tests_run++; \
    if (!(test)) { \
        printf("CRITICAL FAIL: %s - %s (line %d)\n", __func__, message, __LINE__); \
        tests_failed++; \
        current_test_failures++; \
        return; \
    } \
} while(0)

#define RUN_TEST(test) do { \
    current_test_failures = 0; \
    printf("Running %s... ", #test); \
    test(); \
    if (current_test_failures == 0) { \
        printf("PASS\n"); \
    } else { \
        printf("FAIL (%d assertion%s failed)\n", current_test_failures, \
               current_test_failures == 1 ? "" : "s"); \
    } \
} while(0)

#define TEST_SUMMARY() do { \
    printf("\n=== Test Summary ===\n"); \
    printf("Tests run: %d\n", tests_run); \
    printf("Tests failed: %d\n", tests_failed); \
    printf("Tests passed: %d\n", tests_run - tests_failed); \
    if (tests_failed == 0) { \
        printf("All tests PASSED!\n"); \
    } else { \
        printf("Some tests FAILED!\n"); \
    } \
} while(0)

#endif