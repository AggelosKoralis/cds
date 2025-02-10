#include "vector.h"

#include <stdlib.h>
#include <stdio.h>


struct vec {
    int *data;
    long cap;
    long size;
};

void error(char *msg) {
    fprintf(stderr, msg);
}


int extend_vector(vector *v) {
    v->cap *= 2;

    v->data = realloc(v->data, v->cap * sizeof(int));
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
    
    v->data = malloc(v->cap *sizeof(int));
    if (!v->data) {
        free(v); 
        return NULL;
    }

    return v;
}

int vec_push(vector *vec, int data) {
    if (!vec) {
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


// how do i handle errors here
int vec_pop(vector *vec) {

    if (!vec) {
        error("Invalid argument for vec_push().\n");
        return 1;
    }

    if (vec->size <= 0) {
        error("No items to pop.\n");
        return 1;
    }

    return vec->data[--vec->size];
}

int vec_at(vector *vec, long idx) {

    if (!vec) {
        error("Invalid arguments for vec_at.\n");
        return 1;
    }

    if (idx < 0 || idx >= vec->size) {
        error("Index out of bounds.\n");
        return 1;
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
    free(vec->data);
    free(vec);
}