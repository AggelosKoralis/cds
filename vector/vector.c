#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct vec {
    datatype *data;
    uint64_t cap;
    uint64_t size;
    int (*compare)(void *a, void *b);
};

void error(char *msg) {
    fprintf(stderr, msg);
}


int extend_vector(vector v) {
    v->cap *= 2;

    v->data = realloc(v->data, v->cap * sizeof(datatype));
    if (!v->data) return 0;

    return 1;
}


vector vec_init(uint64_t cap, compare_func func) {

    if (cap < 0 || !func) return NULL;

    vector v = malloc(sizeof(struct vec));
    if (!v) return NULL;

    v->cap = cap;
    v->size = 0;
    v->compare = func;

    v->data = malloc(v->cap * sizeof(datatype));
    if (!v->data) {
        free(v); 
        return NULL;
    }

    return v;
}

int vec_push(vector vec, datatype data) {
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


datatype vec_pop(vector vec) {

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

datatype vec_at(vector vec, uint64_t index) {

    if (!vec) {
        error("Invalid arguments for vec_at.\n");
        return NULL;
    }

    if (index < 0 || index >= vec->size) {
        error("Index out of bounds.\n");
        return NULL;
    }

    return vec->data[index];
}

uint64_t vec_size(vector vec) {
    if (!vec) {
        error("Invalid argument for vec_size().\n");
        return 0;
    }

    return vec->size;
}

void swap(datatype *a, datatype *b) {
    datatype c = *a;
    *a = *b;
    *b = c;
}

uint64_t partition(vector vec, uint64_t low, uint64_t high) {
    datatype pivot = vec->data[high];
    // pivot index when the partition is done
    uint64_t piv_idx = low;

    for (uint64_t i = low; i <= high - 1; i++) {
        if (vec->compare(vec->data[i], pivot) <= 0) {
            swap(&vec->data[i], &vec->data[piv_idx]);
            piv_idx += 1;
        }
    }

    swap(&vec->data[piv_idx], &vec->data[high]);
    return piv_idx;
}


void vec_sort(vector vec, uint64_t low, uint64_t high) {
    if (!vec) return;
    if (!vec->data) return;
    if (vec->size == 0) return;
    if (low < 0 || high >= vec->size || low >= high) return;
    if (!vec->compare) return;

    uint64_t p = partition(vec, low, high);

    vec_sort(vec, low, p - 1);
    vec_sort(vec, p + 1, high);
}


void vec_free(vector vec) {
    for (uint64_t i = 0; i <= vec->size; i++)
        free(vec->data[i]);

    free(vec->data); 
    free(vec);
}