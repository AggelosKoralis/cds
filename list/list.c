#include "list.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


struct node {
    void *data;
    struct node *next;
};

struct list {
    Node nodes;
    uint64_t size;
    compare_func compare;
    free_node_func free_node;
};

void boom(char *msg) {
    fprintf(stderr, msg);
    exit(1);
}


void list_default_free_node(Node node) {
    free(node);
}

int list_default_compare(datatype a, datatype b) {
    return a - b;
}


Node list_make_node(datatype data, Node next) {
    Node new_node = malloc(sizeof(struct node));
    if (!new_node) 
        boom("Failed to allocate memory for the new node.\n");

    new_node->data = data;
    new_node->next = next;

    return new_node;
}


List list_init(compare_func compare, free_node_func free_node) {
    
    List new_list = malloc(sizeof(struct list));
    if (!new_list) 
        boom("Failed to allocte memery for the new list.\n");

    new_list->size = 0;
    new_list->nodes = NULL;


    if (!compare) compare = list_default_compare;
    if (!free_node) free_node = list_default_free_node;

    new_list->compare = list_default_compare;
    new_list->free_node = list_default_free_node;

    return new_list;
}

int list_insert_head(List list, datatype data) {
    if (!list) {
        list = list_init(list_default_compare, list_default_free_node);
        if (list_insert_head(list, data) == 0) return 0;
    }

    Node previous_head = list->nodes;

    list->nodes = list_make_node(data, previous_head);
    list->size++;

    return 0;
}


Node list_get_tail(List list) {
    Node node = list->nodes;

    while (node->next) 
        node = node->next;

    return node;
}


int list_insert_tail(List list, datatype data) {
    if (!list) {
        list = list_init(list_default_compare, list_default_free_node);
        // if there are 0 or 1 nodes, head = tail
        if (list_insert_head(list, data) == 0) return 0;
    }
    
    if (!list->nodes) return 1;

    Node previous_tail = list_get_tail(list);

    previous_tail->next = list_make_node(data, NULL);
    list->size++;

    return 0;
}


int list_remove_head(List list) {
    if (!list) return 1;

    Node previous_head = list->nodes->next;
    Node new_head = previous_head->next;

    list_node_free(previous_head, list->free_node);

    list->nodes = new_head;
    list->size--;

    return 0;
}


int list_remove_tail(List list) {
    if (!list) return 1;
    
    Node previous_tail = list_get_tail(list);
    Node new_tail = list_parent(list, previous_tail);

    list_node_free(previous_tail, list->free_node);
    new_tail->next = NULL;
    list->size--;

    return 0;
}


Node list_parent(List list, Node target) {
    if (!list) return NULL;

    Node parent = list->nodes;
    if (!parent) return NULL;
    
    Node child = parent->next;

    while (child) {
        if (child == target) return parent;
        parent = child;
        child = child->next;
    }

    return NULL;
}


Node list_search(List list, datatype target) {
    if (!list) return NULL;
    if (!list->nodes) return NULL;

    Node node = list->nodes;

    while (node) {
        if (list->compare(node->data, target) == 0)
            return node;

        node = node->next;
    }

    return NULL;
}


uint64_t list_size(List list) {
    return list == NULL ? 0 : list->size;
}


void list_node_free(Node node, free_node_func free_node) {
    if (free_node) free_node(node);
}


void list_free(List list) {
    if (!list) return;
    if (!list->nodes) return;
    if (!list->free_node) ;

    Node node = list->nodes;

    while (node->next) {
        Node temp = node;
        node = node->next;
        list->free_node(temp);
    }

    free(list);
}