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
};

void boom(char *msg) {
    fprintf(stderr, msg);
    exit(1);
}


Node list_make_node(datatype data, Node next) {
    Node new_node = malloc(sizeof(struct node));
    if (!new_node) 
        boom("Failed to allocate memory for the new node.\n");

    new_node->data = data;
    new_node->next = next;

    return new_node;
}


List list_init(void) {
    List new_list = malloc(sizeof(struct list));
    if (!new_list) 
        boom("Failed to allocte memery for the new list.\n");

    new_list->size = 0;
    new_list->nodes = NULL;

    return new_list;
}

int list_insert_head(List list, datatype data) {
    if (!list) {
        list = list_init();
        if (list_insert_head(list, data) == 0) return 0;
    }

    Node previous_head = list->nodes;

    list->nodes = list_make_node(data, previous_head);
    list->size++;

    return 0;
}


Node list_get_tail(List list) {
    Node head = list->nodes;

    while (head->next) 
        head = head->next;

    return head;
}


int list_insert_tail(List list, datatype data) {
    if (!list) {
        list = list_init();
        // if there are 0 or 1 nodes, head = tail
        if (list_insert_head(list, data) == 0) return 0;
    }
    
    Node previous_tail = list_get_tail(list);

    previous_tail->next = list_make_node(data, NULL);
    list->size++;

    return 0;
}


int list_remove_head(List list) {
    if (!list) return 1;

    Node previous_head = list->nodes->next;
    Node new_head = previous_head->next;

    list_node_free(previous_head);

    list->nodes = new_head;
    list->size--;

    return 0;
}


int list_remove_tail(List list) {
    if (!list) return 1;
    
    Node previous_tail = list_get_tail(list);



    list->size--;

    return 0;
}