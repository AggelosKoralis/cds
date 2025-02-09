#ifndef BST_H
#define BST_H

typedef struct bst BST;

BST *bst_init(void);
BST *bst_insert(BST *bst, void **data, int *(compare)(void **p1, void **p2));
BST *bst_remove(BST *bst, void **data);
BST *bst_search(BST *bst, void **data/*, int *(compare)(void **p1, void **p2)*/);
void bst_free();

#endif