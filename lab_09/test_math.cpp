#include <cstdio>
#include <cstdlib>
#include <ctime>

#define ITERATIONS 1e7

template <typename Type>
void time_mesurement_cpp(unsigned int times, Type a, Type b)
{
    Type result;

    clock_t start = clock();

    for (size_t i = 0; i < times; i++)
        result = a + b;

    clock_t time_sum = clock() - start;

    start = clock();

    for (size_t i = 0; i < times; i++)
        result = a * b;

    clock_t time_mul = clock() - start;

    printf("Addition: %zu ms    Multiplication: %zu ms\n", time_sum, time_mul);
}

template <typename Type>
void time_mesurement_asm(unsigned int times, Type a, Type b)
{
    Type result;

    clock_t start = clock();

    for (size_t i = 0; i < times; i++)
        __asm__("fld %1;"
                "fld %2;"
                "faddp;"
                "fstp %0;"
                : "=m"(result)
                : "m"(a),
                  "m"(b)
                );

    clock_t time_sum = clock() - start;

    start = clock();

    for (size_t i = 0; i < times; ++i)
        __asm__("fld %1;"
                "fld %2;"
                "fmulp;"
                "fstp %0;"
                : "=m"(result)
                : "m"(a),
                  "m"(b)
                );

    clock_t time_mul = clock() - start;

    printf("Addition: %zu ms    Multiplication: %zu ms\n", time_sum, time_mul);
}

#ifdef ASM
#define TIME_MEASUREMENT(Type) time_mesurement_asm<Type>
#else
#define TIME_MEASUREMENT(Type) time_mesurement_cpp<Type>
#endif

int main()
{
    double number_1 = -1.23, number_2 = 1023.1;

    printf("Float:          ");
    TIME_MEASUREMENT(float)(ITERATIONS, number_1, number_2);

    printf("Double:         ");
    TIME_MEASUREMENT(double)(ITERATIONS, number_1, number_2);

#ifdef FLOAT_80
    printf("80-bit float:      ");
    TIME_MEASUREMENT(__float80)(ITERATIONS, number_1, number_2);
#endif

#ifndef SSE
    printf("Long double:    ");
    TIME_MEASUREMENT(long double)(ITERATIONS, number_1, number_2);
#endif

    return EXIT_SUCCESS;
}