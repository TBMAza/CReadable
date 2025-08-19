#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "../src/creadable.h"

// ===========================
// Test framework
// ===========================
static int total_tests = 0;
static int passed_tests = 0;
static int failed_tests = 0;

#define ASSERT_EQ_INT(fn, input, expected) do { \
    total_tests++; \
    int result = fn(input); \
    if(result == expected) { \
        passed_tests++; \
        printf("[PASS] %s(\"%s\") = %d\n", #fn, input, result); \
    } else { \
        failed_tests++; \
        printf("[FAIL] %s(\"%s\") = %d (expected %d)\n", #fn, input, result, expected); \
    } \
} while(0)

#define ASSERT_EQ_UINT(fn, input, expected) do { \
    total_tests++; \
    unsigned int result = fn(input); \
    if(result == expected) { \
        passed_tests++; \
        printf("[PASS] %s(\"%s\") = %u\n", #fn, input, result); \
    } else { \
        failed_tests++; \
        printf("[FAIL] %s(\"%s\") = %u (expected %u)\n", #fn, input, result, expected); \
    } \
} while(0)

#define ASSERT_EQ_LONG(fn, input, expected) do { \
    total_tests++; \
    long result = fn(input); \
    if(result == expected) { \
        passed_tests++; \
        printf("[PASS] %s(\"%s\") = %ld\n", #fn, input, result); \
    } else { \
        failed_tests++; \
        printf("[FAIL] %s(\"%s\") = %ld (expected %ld)\n", #fn, input, result, expected); \
    } \
} while(0)

#define ASSERT_EQ_ULONG(fn, input, expected) do { \
    total_tests++; \
    unsigned long result = fn(input); \
    if(result == expected) { \
        passed_tests++; \
        printf("[PASS] %s(\"%s\") = %lu\n", #fn, input, result); \
    } else { \
        failed_tests++; \
        printf("[FAIL] %s(\"%s\") = %lu (expected %lu)\n", #fn, input, result, expected); \
    } \
} while(0)

#define ASSERT_EQ_LLONG(fn, input, expected) do { \
    total_tests++; \
    long long result = fn(input); \
    if(result == expected) { \
        passed_tests++; \
        printf("[PASS] %s(\"%s\") = %lld\n", #fn, input, result); \
    } else { \
        failed_tests++; \
        printf("[FAIL] %s(\"%s\") = %lld (expected %lld)\n", #fn, input, result, expected); \
    } \
} while(0)

#define ASSERT_EQ_ULLONG(fn, input, expected) do { \
    total_tests++; \
    unsigned long long result = fn(input); \
    if(result == expected) { \
        passed_tests++; \
        printf("[PASS] %s(\"%s\") = %llu\n", #fn, input, result); \
    } else { \
        failed_tests++; \
        printf("[FAIL] %s(\"%s\") = %llu (expected %llu)\n", #fn, input, result, expected); \
    } \
} while(0)

#define ASSERT_EQ_FLOAT(fn, input, expected) do { \
    total_tests++; \
    float result = fn(input); \
    if(fabsf(result - expected) < 1e-6f) { \
        passed_tests++; \
        printf("[PASS] %s(\"%s\") = %f\n", #fn, input, result); \
    } else { \
        failed_tests++; \
        printf("[FAIL] %s(\"%s\") = %f (expected ~%f)\n", #fn, input, result, expected); \
    } \
} while(0)

#define ASSERT_EQ_DOUBLE(fn, input, expected) do { \
    total_tests++; \
    double result = fn(input); \
    if(fabs(result - expected) < 1e-12) { \
        passed_tests++; \
        printf("[PASS] %s(\"%s\") = %lf\n", #fn, input, result); \
    } else { \
        failed_tests++; \
        printf("[FAIL] %s(\"%s\") = %lf (expected ~%lf)\n", #fn, input, result, expected); \
    } \
} while(0)

#define ASSERT_EQ_LDOUBLE(fn, input, expected) do { \
    total_tests++; \
    long double result = fn(input); \
    if(fabsl(result - expected) < 1e-12L) { \
        passed_tests++; \
        printf("[PASS] %s(\"%s\") = %Lf\n", #fn, input, result); \
    } else { \
        failed_tests++; \
        printf("[FAIL] %s(\"%s\") = %Lf (expected ~%Lf)\n", #fn, input, result, expected); \
    } \
} while(0)


// ===========================
// Main tests
// ===========================
int main(void) {
    char buf[64];

    printf("==== VALID INTEGERS ====\n");
    ASSERT_EQ_INT(_rint, "123", 123);
    ASSERT_EQ_INT(_rint, "1_234", 1234);
    ASSERT_EQ_INT(_rint, "1,234,567", 1234567);
    ASSERT_EQ_INT(_rint, "   -42", -42);
    ASSERT_EQ_UINT(_ruint, "42", 42);
    ASSERT_EQ_UINT(_ruint, "12 345", 12345);

    printf("\n==== VALID FLOATS ====\n");
    ASSERT_EQ_FLOAT(_rfloat, "3.14", 3.14f);
    ASSERT_EQ_FLOAT(_rfloat, "1_234.567", 1234.567f);
    ASSERT_EQ_DOUBLE(_rdouble, "2.71828", 2.71828);
    ASSERT_EQ_LDOUBLE(_rlongdouble, "-0.001", -0.001L);

    printf("\n==== BOUNDARY TESTS ====\n");
    sprintf(buf, "%d", INT_MAX);
    ASSERT_EQ_INT(_rint, buf, INT_MAX);
    sprintf(buf, "%d", INT_MIN);
    ASSERT_EQ_INT(_rint, buf, INT_MIN);

    sprintf(buf, "%ld", LONG_MAX);
    ASSERT_EQ_LONG(_rlong, buf, LONG_MAX);
    sprintf(buf, "%ld", LONG_MIN);
    ASSERT_EQ_LONG(_rlong, buf, LONG_MIN);

    sprintf(buf, "%lld", LLONG_MAX);
    ASSERT_EQ_LLONG(_rlonglong, buf, LLONG_MAX);
    sprintf(buf, "%lld", LLONG_MIN);
    ASSERT_EQ_LLONG(_rlonglong, buf, LLONG_MIN);

    sprintf(buf, "%u", UINT_MAX);
    ASSERT_EQ_UINT(_ruint, buf, UINT_MAX);
    sprintf(buf, "%lu", ULONG_MAX);
    ASSERT_EQ_ULONG(_rulong, buf, ULONG_MAX);
    sprintf(buf, "%llu", ULLONG_MAX);
    ASSERT_EQ_ULLONG(_rulonglong, buf, ULLONG_MAX);

    printf("\n==== FLOAT BOUNDARIES ====\n");
    sprintf(buf, "%.6e", FLT_MAX);
    ASSERT_EQ_FLOAT(_rfloat, buf, FLT_MAX);
    sprintf(buf, "%.6e", FLT_MIN);
    ASSERT_EQ_FLOAT(_rfloat, buf, FLT_MIN);

    sprintf(buf, "%.15e", DBL_MAX);
    ASSERT_EQ_DOUBLE(_rdouble, buf, DBL_MAX);
    sprintf(buf, "%.15e", DBL_MIN);
    ASSERT_EQ_DOUBLE(_rdouble, buf, DBL_MIN);

    printf("\n==== ZERO HANDLING ====\n");
    ASSERT_EQ_INT(_rint, "0", 0);
    ASSERT_EQ_INT(_rint, "-0", 0);
    ASSERT_EQ_INT(_rint, "0000", 0);
    ASSERT_EQ_FLOAT(_rfloat, "0.0", 0.0f);

    printf("\n==== WHITESPACE HANDLING ====\n");
    ASSERT_EQ_INT(_rint, "   123   ", 123);
    ASSERT_EQ_INT(_rint, "\t 456 \t", 456);

    printf("\n==== MIXED SEPARATORS AT BOUNDARIES ====\n");
    ASSERT_EQ_LLONG(_rlonglong, "9_223_372_036_854_775_807", LLONG_MAX);
    ASSERT_EQ_ULLONG(_rulonglong, "18,446,744,073,709,551,615", ULLONG_MAX);

    printf("\n==== INVALID INPUTS ====\n");
    ASSERT_EQ_INT(_rint, "12a34", 0);
    ASSERT_EQ_INT(_rint, "1_2,3", 0);
    ASSERT_EQ_INT(_rint, "12.34", 0);
    ASSERT_EQ_FLOAT(_rfloat, "1234", 0.0f);
    ASSERT_EQ_INT(_rint, "", 0);
    ASSERT_EQ_UINT(_ruint, "-42", 0);

    printf("\n==== OVERFLOW/UNDERFLOW ====\n");
    ASSERT_EQ_INT(_rint, "999999999999999", 0);
    ASSERT_EQ_UINT(_ruint, "999999999999999", 0);
    ASSERT_EQ_LONG(_rlong, "-99999999999999999999999", 0);

    printf("\n==== SUMMARY ====\n");
    printf("Total: %d | Passed: %d | Failed: %d\n",
           total_tests, passed_tests, failed_tests);

    return (failed_tests == 0) ? 0 : 1;
}

