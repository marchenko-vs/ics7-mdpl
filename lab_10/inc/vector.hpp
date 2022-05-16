#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

typedef struct
{
    float array[4];
} vector_t;

vector_t init(const float x, const float y, const float z);
float cpp_scalar_production(const vector_t *const vector_a, const vector_t *const vector_b);
float sse_scalar_production(const vector_t *const vector_a, const vector_t *const vector_b);

#endif // _VECTOR_HPP_
