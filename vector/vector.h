#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct vec *vector;


vector vec_init(long cap);
int vec_push(vector vec, int data);
int vec_pop(vector vec);
int vec_at(vector vec, long idx);
size_t vec_size(vector vec);
void vec_sort(vector vec, long low, long high);
void vec_free(vector vec);

#endif