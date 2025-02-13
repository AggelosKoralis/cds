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


int extend_vector(vector v) {
    v->cap *= 2;

    v->data = realloc(v->data, v->cap * sizeof(int));
    if (!v->data) return 0;

    return 1;
}


vector vec_init(long cap) {

    if (cap < 0) {
        error("Tried to initialize vector with negative capacity.\n");
        return NULL;
    }

    vector v = malloc(sizeof(struct vec));
    if (!v) return NULL;

    v->cap = cap;
    v->size = 0;
    
    v->data = malloc(v->cap * sizeof(int));
    if (!v->data) {
        free(v); 
        return NULL;
    }

    return v;
}

int vec_push(vector vec, int data) {
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
int vec_pop(vector vec) {

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

int vec_at(vector vec, long idx) {

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

size_t vec_size(vector vec) {
    if (!vec) {
        error("Invalid argument for vec_size().\n");
        return 0;
    }

    return vec->size;
}

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

long partition(vector vec, long low, long high) {
    int pivot = vec->data[high];
    // pivot index when the partition is done
    long piv_idx = low;

    for (long j = low; j <= high - 1; j++) {
        if (vec->data[j] <= pivot) {
            swap(&vec->data[j], &vec->data[piv_idx]);
            piv_idx += 1;
        }
    }

    swap(&vec->data[piv_idx], &vec->data[high]);
    return piv_idx;
}


void vec_sort(vector vec, long low, long high) {
    if (!vec) return;
    if (!vec->data) return;
    if (vec->size == 0) return;
    if (low < 0 || high >= vec->size || low >= high) return;


    long p = partition(vec, low, high);

    vec_sort(vec, low, p - 1);
    vec_sort(vec, p + 1, high);
}


void vec_free(vector vec) {
    free(vec->data); 
    free(vec);
}