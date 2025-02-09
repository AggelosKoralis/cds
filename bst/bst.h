#ifndef BST_H
#define BST_H

typedef struct bst BST;

BST *bst_init(void);
BST *bst_insert(void *data);
BST *bst_remove(void *data);
BST *bst_search(BST *bst, void **data, int *(compare)(void **p1, void **p2));


#endif