#include <stdlib.h>
#include "vector.h"

vector_t *vector_create(size_t size)
{
    vector_t *vec = malloc(sizeof(vector_t));
    if (!vec) return NULL;

    vec->items = malloc(sizeof(double) * size);
    if (!vec->items) {
        free(vec);
        return NULL;
    }

    vec->size = 0;
    return vec;
}

void vector_destroy(vector_t *vec)
{
    if (vec) {
        free(vec->items);
        free(vec);
    }
}

double vector_set(vector_t *vec, size_t index, double value)
{
    if (index >= vec->size) return 0.0; // or handle error

    double old_value = vec->items[index];
    vec->items[index] = value;
    return old_value;
}

double vector_get(const vector_t *vec, size_t index)
{
    if (index >= vec->size) return 0.0; // or handle error

    return vec->items[index];
}

vector_t *vector_by_element(double op(double,double), const vector_t *a, const vector_t *b)
{
    if (a->size != b->size) return NULL;

    vector_t *result = vector_create(a->size);
    if (!result) return NULL;

    for (size_t i = 0; i < a->size; i++) {
        result->items[i] = op(a->items[i], b->items[i]);
    }
    result->size = a->size;

    return result;
}

double plus(double x, double y) { return x + y; }
vector_t *vector_add(const vector_t *a, const vector_t *b)
{
    return vector_by_element(plus, a, b);
}

double minus(double x, double y) { return x - y; }
vector_t *vector_sub(const vector_t *a, const vector_t *b)
{
    return vector_by_element(minus, a, b);
}

double multiply(double x, double y) { return x * y; }
vector_t *vector_mul(const vector_t *a, const vector_t *b)
{
    return vector_by_element(multiply, a, b);
}

double divide(double x, double y) { return x / y; }
vector_t *vector_div(const vector_t *a, const vector_t *b)
{
    return vector_by_element(divide, a, b);
}

vector_t *vector_concatenate(const vector_t *a, const vector_t *b)
{
    vector_t *result = vector_create(a->size + b->size);
    if (!result) return NULL;

    for (size_t i = 0; i < a->size; i++) {
        result->items[i] = a->items[i];
    }
    for (size_t i = 0; i < b->size; i++) {
        result->items[a->size + i] = b->items[i];
    }
    result->size = a->size + b->size;

    return result;
}

vector_t *vector_scalar_product(const vector_t *a, const vector_t *b)
{
    if (a->size != b->size) return NULL;

    vector_t *result = vector_create(1);
    if (!result) return NULL;

    double sum = 0.0;
    for (size_t i = 0; i < a->size; i++) {
        sum += a->items[i] * b->items[i];
    }
    result->items[0] = sum;
    result->size = 1;

    return result;
}

