#ifndef BST_H
#define BST_H

typedef struct bst BST;

BST *bst_init(int data);
BST *bst_insert(BST *bst, int data);
BST *bst_remove(BST *bst, int data);
BST *bst_search(BST *bst, int data);
void bst_inorder(BST *bst);
void bst_free(BST *bst);

#endif