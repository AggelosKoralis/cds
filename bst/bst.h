#ifndef BST_H
#define BST_H

typedef struct bst *BST;
typedef struct node *Node;

BST bst_init(int data);
void bst_insert(BST bst, int data);
void bst_remove(BST bst, int data);
Node bst_search(BST bst, int data);
void bst_inorder(BST bst);
void bst_preorder(BST bst);
void bst_postorder(BST bst);
void bst_free(BST bst);

#endif