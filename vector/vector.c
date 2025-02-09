#include "vector.h"

#include <stdlib.h>
#include <stdio.h>


struct vec {
    void **data; // array of void * things
    long cap;
    long size;
};

void error(char *msg) {
    fprintf(stderr, msg);
}


int extend_vector(vector *v) {
    v->cap *= 2;

    v->data = realloc(v->data, v->cap * sizeof(void *));
    if (!v->data) return 0;

    return 1;
}


vector *vec_init(long cap) {

    if (cap < 0) {
        error("Tried to initialize vector with negative capacity.\n");
        return NULL;
    }

    vector *v = malloc(sizeof(vector));
    if (!v) return NULL;

    v->cap = cap;
    v->size = 0;
    
    v->data = malloc(v->cap *sizeof(void *));
    if (!v->data) {
        free(v); 
        return NULL;
    }

    return v;
}

int vec_push(vector *vec, void *data) {
    if (!vec || !data) {
        error("Invalid arguments for vec_push().\n");
        return -1;
    }

    if (vec->size >= vec->cap) {
        if (!extend_vector(vec)) {
            error("Failed to extend vector.\n");
            return 1;
        }
    }

    vec->data[vec->size++] = data;
    return 0;
}

void *vec_pop(vector *vec) {

    if (!vec) {
        error("Invalid argument for vec_push().\n");
        return NULL;
    }

    if (vec->size <= 0) {
        error("No items to pop.\n");
        return NULL;
    }

    return vec->data[--vec->size];
}

void *vec_at(vector *vec, long idx) {

    if (!vec) {
        error("Invalid arguments for vec_at.\n");
        return NULL;
    }

    if (idx < 0 || idx >= vec->size) {
        error("Index out of bounds.\n");
        return NULL;
    }

    return vec->data[idx];
}

size_t vec_size(vector *vec) {
    if (!vec) {
        error("Invalid argument for vec_size().\n");
        return 0;
    }

    return vec->size;
}

void vec_free(vector *vec) {
    for (int i = 0; i < vec->size; i++)
        free(vec->data[i]);
    free(vec->data);
    free(vec);
}