#include <stdio.h>
#include "vector.h"
#include <time.h>

// == 0 on equal
// < 0 on a < b
// > 0 on a > b
int compare(int *a, int *b) {
    return *a - *b;
}

int main() {
    srand(time(NULL));

    compare_func func = compare;
    vector vec = vec_init(10, func);
    if (!vec) return 1;

    for (int i = 0; i < 6; i++) {
        int *e = malloc(sizeof(int));
        if (!e) return 1;

        *e = rand() % 100;
        if (vec_push(vec, e) != 0) return 1;
    }

    for (uint64_t i = 0; i < vec_size(vec); i++) 
        printf("vec[%d] = %d\n", i, *(int *)vec_at(vec, i));


    vec_sort(vec, 0, vec_size(vec) - 1);
    
    printf("\nSorted vector:\n");
    for (uint64_t i = 0; i < vec_size(vec); i++) 
        printf("vec[%d] = %d\n", i, *(int *)vec_at(vec, i));

    vec_free(vec);

    return 0;
}