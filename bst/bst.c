#include "bst.h"

#include <stdio.h>


struct bst {
    void **data;
    struct bst *left;
    struct bst *right;
};

void error(char *msg) {
    fprintf(stderr, msg);
}


BST *bst_init(void) {
    BST *bst = malloc(sizeof(BST));
    if (!bst) {
        error("Failed to initialize the bst.\n");
        return NULL;
    }

    bst->data = malloc(sizeof(void *));
    if (!bst->data) {
        error("Failed to allocate memory for the data.\n");
        return NULL;
    }

    bst->left = NULL;
    bst->right = NULL;

    return bst;
}


BST *bst_make_node(void **data) {
    BST *node = malloc(sizeof(BST));
    if (!node) {
        error("Failed to create node.\n");
        return NULL;
    }

    node->data = malloc(sizeof(void *));
    if (!node->data) {
        error("Failed to allocate memory for the data.\n");
        return NULL;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

BST *run_insert(BST *root, void **data, int *(compare)(void **p1, void **p2)) {
    if (!root) return bst_make_node(data);

    if (compare(root->data, data) < 0) 
        return run_insert(root->right, data, compare);
    if (compare(root->data, data) > 0) 
        return run_insert(root->left, data, compare);

    // already exists ig
    return root;
}


BST *bst_insert(BST *bst, void **data, int *(compare)(void **p1, void **p2)) {
    if (!data) {
        error('Invalid arguments for bst_insert().\n');
        return NULL;
    }

    if (!bst) return bst_make_node(data);
    
    return run_insert(bst, data, compare);
}


BST *run_search(BST *root, void **data, int *(compare)(void **p1, void **p2)) {
    if (!root) return NULL;
    
    if (compare(root->data, data) == 0) return root;

    if (compare(root->data, data) < 0) 
        return run_search(root->right, data, compare);
    if (compare(root->data, data) > 0) 
        return run_search(root->left, data, compare);

    return NULL;
}


int func(void **p1, void **p2) {
    int n1 = **(int **)p1;
    int n2 = **(int **)p2;

    if (n1 == n2) return 0;
    else if (n1 < n2) return -1;
    else if (n1 > n2) return 1;

    return 0;
}

BST *bst_search(BST *bst, void **data/*, int *(compare)(void **p1, void **p2)*/) {
    if (!data) {
        error("Invalid data to search.\n");
        return NULL;
    }

    int *compare = func;
    BST *target = run_search(bst, data, compare);
    if (!target)
        error("Data not found.\n");

    return target;
}