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

    __asm__(".intel_syntax noprefix;"
            "movaps xmm0, %1;"
            "movaps xmm1, %2;"
            "mulps xmm0, xmm1;"      // Параллельное умножение четырех пар чисел с плавающей запятой
            "movhlps xmm1, xmm0;"    // Копирование старших 64 бит источника в младшие 64 бита приемника
            "addps xmm0, xmm1;"      // Параллельное сложение четырех пар чисел с плавающей запятой
            "movaps xmm1, xmm0;"   
            "shufps xmm0, xmm0, 1;"  // В младшие два числа приемника помещаются любые из четырех чисел,
                                     // находившихся в приемнике [приемник, источник, индекс]
            "addps xmm0, xmm1;"
            "movss %0, xmm0;"        // Копирование младших 64 бит из источника в приемник
    :"=m"(result)
    :"m"(vector_a->array), "m"(vector_b->array)
    :"xmm0", "xmm1");

    return result;
}
