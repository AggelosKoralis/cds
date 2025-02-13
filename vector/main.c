#include <stdio.h>
#include "vector.h"
#include <time.h>

int main() {
    srand(time(NULL));

    vector vec = vec_init(10);
    if (!vec) return 1;

    for (int i = 0; i < 6; i++) 
        if (vec_push(vec, rand() % 100) != 0) return 1;

    for (int i = 0; i < vec_size(vec); i++) 
        printf("vec[%d] = %d\n", i, vec_at(vec, i));

    vec_sort(vec, 0, vec_size(vec) - 1);
    
    printf("\nSorted vector:\n");
    for (int i = 0; i < vec_size(vec); i++) 
        printf("vec[%d] = %d\n", i, vec_at(vec, i));

    vec_free(vec);

    return 0;
}