#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <windows.h>

#include "vector.hpp"

#define ITERATIONS 10000

#define EPS 1e-3

static bool are_equal(const float a, const float b)
{
    if (fabs(a - b) <= EPS)
        return true;

    return false;
}

static void unit_test(size_t iterations)
{
    float a = 56.98;
    float b = -32.54;
    float c = 198.0;

    float result_cpp = 0.0;
    float result_sse_asm = 0.0;

    vector_t vector_a = init(a, b, c);
    vector_t vector_b = init(a, b, c);

    printf("---Testing CPP implementation---\n");

	LARGE_INTEGER start;
    LARGE_INTEGER end;

	QueryPerformanceCounter(&start);

    for (size_t i = 0; i < iterations; i++) 
        result_cpp = cpp_scalar_production(&vector_a, &vector_b);

	QueryPerformanceCounter(&end);

    printf("Result = %.3f\nTime = %.3g s\n\n", result_cpp, 
        (double)(end.QuadPart - start.QuadPart) / ITERATIONS);

    printf("---Testing SSE-ASM implementation---\n");

    QueryPerformanceCounter(&start);

    for (size_t i = 0; i < iterations; i++) 
        result_sse_asm = sse_scalar_production(&vector_a, &vector_b);

    QueryPerformanceCounter(&end);

    printf("Result = %.3f\nTime = %.3g s\n\n", result_sse_asm, 
        (double)(end.QuadPart - start.QuadPart) / ITERATIONS);

    if (are_equal(result_cpp, result_sse_asm))
        printf("Test result: SUCCESS.\n");
    else
        printf("Test result: FAILURE.\n");
}

int main()
{
    unit_test(ITERATIONS);

    return EXIT_SUCCESS;
}
