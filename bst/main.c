//i dont need these mains
#include <stdio.h>

#include "bst.h"

int main(void) {
    BST tree = bst_init(5);
    if (!tree) {
        return 1;
    }

    bst_insert(tree, 10);
    bst_insert(tree, 1);

    bst_insert(tree, 25);
    bst_insert(tree, 1);

    bst_insert(tree, 9);
    bst_insert(tree, 1);

    bst_inorder(tree);
    putchar(10);

    bst_preorder(tree);
    putchar(10);

    bst_postorder(tree);
    putchar(10);

    bst_free(tree);

    return 0;    
}