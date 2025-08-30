#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct _vector {
    double *items;
    size_t size;
} vector_t;

vector_t *vector_create(size_t size);
void vector_destroy(vector_t *vec);

double vector_set(vector_t *vec, size_t index, double value);
double vector_get(const vector_t *vec, size_t index);

vector_t *vector_add(const vector_t *a, const vector_t *b);
vector_t *vector_sub(const vector_t *a, const vector_t *b);
vector_t *vector_mul(const vector_t *a, const vector_t *b);
vector_t *vector_div(const vector_t *a, const vector_t *b);

vector_t *vector_concatenate(const vector_t *a, const vector_t *b);
vector_t *vector_scalar_product(const vector_t *a, const vector_t *b);

#endif /* VECTOR_H */
