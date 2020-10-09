#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct ll_node {
    int value;
    struct ll_node* next;
} ll_node_t;

typedef struct {
    ll_node_t* data;
} linked_list_t;

typedef enum {
    LL_SUCCESS,
    LL_ALLOCATION_ERROR,
    LL_OUT_OF_DATA_ERROR
} LL_RETURN_t;


linked_list_t* newLL();
LL_RETURN_t pushToLL(linked_list_t*, int);
LL_RETURN_t popFromLL(linked_list_t*, int*);
void printLL(linked_list_t*);

#endif // LINKEDLIST_H_
