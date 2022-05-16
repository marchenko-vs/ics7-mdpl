#include "vector.hpp"

vector_t init(const float x, const float y, const float z)
{
    vector_t vector = { 0 };

    vector.array[0] = x;
    vector.array[1] = y;
    vector.array[2] = z;

    return vector;
}

float cpp_scalar_production(const vector_t *const vector_a, const vector_t *const vector_b)
{
    float result = 0;

    result = vector_a->array[0] * vector_b->array[0] +
             vector_a->array[1] * vector_b->array[1] +
             vector_a->array[2] * vector_b->array[2];

    return result;
}

float sse_scalar_production(const vector_t *const vector_a, const vector_t *const vector_b)
{
    float result = 0;

    __asm__(".intel_syntax noprefix\n\t"
            "movaps xmm0, %1\n\t"
            "movaps xmm1, %2\n\t"
            "mulps xmm0, xmm1\n\t"      // Выполняет параллельное умножение четырех пар чисел с плавающей запятой. Результат записывается в приемник
            "movhlps xmm1, xmm0\n\t"    // Копирует старшие 64 бита источника в младшие 64 бита приемника.
            "addps xmm0, xmm1\n\t"      // Выполняет параллельное сложение четырех пар чисел с плавающей запятой. Результат записывается в приемник.
            "movaps xmm1, xmm0\n\t"   
            "shufps xmm0, xmm0, 1\n\t"  // В младшие два числа приемника помещает любые из четырех чисел, находившихся в приемнике [пр, ист, индекс]
            "addps xmm0, xmm1\n\t"
            "movss %0, xmm0\n\t"        // Копирует младшие 64 бита из источника в приемник
    :"=m"(result)
    :"m"(vector_a->array), "m"(vector_b->array)
    :"xmm0", "xmm1");

    return result;
}
