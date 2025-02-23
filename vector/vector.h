#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdint.h>

typedef void * datatype;
typedef int (*compare_func)(datatype a, datatype b);
typedef struct vec *vector;


vector vec_init(uint64_t cap, compare_func func);
int vec_push(vector vec, datatype data);
datatype vec_pop(vector vec);
datatype vec_at(vector vec, uint64_t index);
uint64_t vec_size(vector vec);
void vec_sort(vector vec, uint64_t low, uint64_t high);
void vec_free(vector vec);

#endif