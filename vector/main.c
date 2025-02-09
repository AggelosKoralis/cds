#include <stdio.h>
#include "vector.h"

int main() {
    
    vector *vec = vec_init(10);
    if (!vec) return 1;

    for (int i = 0; i < 6; i++) {
        int *num = malloc(sizeof(int));
        if (!num) return 1;
        
        *num = i;
        if (vec_push(vec, num) != 0) return 1;
    }

    for (int i = 0; i < vec_size(vec); i++) 
        printf("vec[%d] = %d\n", i, *(int *)vec_at(vec, i));

    vec_free(vec);

    return 0;
}