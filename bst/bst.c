#include "bst.h"

#include <stdio.h>
#include <stdlib.h>


struct bst {
    size_t num_nodes;
    size_t depth;
    Node root;
};

struct node {
    int data;
    Node left;
    Node right;
};


Node bst_make_node(int data) {
    Node node = malloc(sizeof(struct node));
    if (!node) return NULL;

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

BST bst_init(int data) {
    BST bst = malloc(sizeof(struct bst));
    if (!bst) return NULL;

    bst->depth = 1;
    bst->num_nodes = 1;
    bst->root = bst_make_node(data);

    return bst;
}

Node run_insert(Node root, int data) {
    if (!root) return bst_make_node(data);

    if (data < root->data)
        root->left = run_insert(root->left, data);
    if (data > root->data) 
        root->right = run_insert(root->right, data);

    return root;
}

// need to update the depth and num nodes variables
void bst_insert(BST bst, int data) {
    if (!bst) {
        bst->root = bst_make_node(data);
        return;
    }
    run_insert(bst->root, data);
}

// return a ptr to the node
// null if not found
Node run_search(Node root, int data) {
    if (!root) return NULL;
    
    if (data == root->data) return root;

    if (data < root->data) 
        return run_search(root->left, data);
    if (data > root->data) 
        return run_search(root->right, data);

    return NULL; 
}

Node bst_search(BST bst, int data) {
    Node target = run_search(bst->root, data);

    return target;
}

void run_inorder(Node root) {
    if (!root) return;

    run_inorder(root->left);
    printf("-%d-", root->data);
    run_inorder(root->right);
}

void bst_inorder(BST bst) {
    run_inorder(bst->root);
}

void run_preorder(Node root) {
    if (!root) return;

    printf("-%d-", root->data);
    run_preorder(root->left);
    run_preorder(root->right);
}

void bst_preorder(BST bst) {
    run_preorder(bst->root);
}


void run_postorder(Node root) {
    if (!root) return;

    run_postorder(root->left);
    run_postorder(root->right);
    printf("-%d-", root->data);
}

void bst_postorder(BST bst) {
    run_postorder(bst->root);
}

void run_free(Node root) {
    if (!root) return;


    if (root->left) run_free(root->left);
    if (root->right) run_free(root->right);

    free(root);
    return;
}

void bst_free(BST bst) {
    run_free(bst->root);
    free(bst);
}