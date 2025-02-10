#include "bst.h"

#include <stdio.h>
#include <stdlib.h>


struct bst {
    int data;
    struct bst *left;
    struct bst *right;
};

void error(char *msg) {
    fprintf(stderr, msg);
}

BST *bst_make_node(int data) {
    BST *node = malloc(sizeof(BST));
    if (!node) {
        error("Failed to create node.\n");
        return NULL;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

BST *bst_init(int data) {
    return bst_make_node(data);
}

BST *run_insert(BST *root, int data) {
    if (!root) return bst_make_node(data);

    if (data < root->data)
        root->left = run_insert(root->left, data);
    if (data > root->data) 
        root->right = run_insert(root->right, data);

    return root;
}


BST *bst_insert(BST *bst, int data) {
    if (!bst) return bst_make_node(data);
    
    return run_insert(bst, data);
}


BST *run_search(BST *root, int data) {
    if (!root) return NULL;
    
    if (data == root->data) return root;

    if (data < root->data) 
        return run_search(root->left, data);
    if (data > root->data) 
        return run_search(root->right, data);

    // not found
    return NULL; 
}

BST *bst_search(BST *bst, int data) {
    BST *target = run_search(bst, data);

    return target;
}

void run_inorder(BST *root) {
    if (!root) return;

    run_inorder(root->left);
    printf("-%d-", root->data);
    run_inorder(root->right);

    return;
}

void bst_inorder(BST *bst) {
    run_inorder(bst);
}