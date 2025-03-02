#ifndef LIST_H
#define LIST_H

#include <stdint.h>

typedef void * datatype;
typedef struct list *List;
typedef struct node *Node;
typedef int (*compare_func)(datatype a, datatype b);
typedef void (*free_node_func)(Node node);


List list_init(compare_func compare, free_node_func free_node);
int list_insert_head(List list, datatype data);
int list_insert_tail(List list, datatype data);
int list_remove_head(List list);
int list_remove_tail(List list);
int list_sort(List list);
Node list_parent(List list, Node target);
Node list_search(List list, datatype target);
uint64_t list_size(List list);
void list_free(List list);

// freeing a node that is the head of a sub-list of the whole list 
// will cause a leak in memory and loss of data
void list_node_free(Node node, free_node_func free_node);


#endif