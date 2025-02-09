#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct vec vector;


vector *vec_init(long cap);
int vec_push(vector *vec, void *data);
void *vec_pop(vector *vec);
void *vec_at(vector *vec, long idx);
size_t vec_size(vector *vec);
void vec_free(vector *vec);

#endif