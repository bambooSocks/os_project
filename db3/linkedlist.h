#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct ll_node {
    int value;
    struct ll_node next;
} linked_list_t;

void pushToLL(linked_list_t*, int);
int popFromLL(linked_list_t*);
void printLL(linked_list_t*);

#endif // LINKEDLIST_H_
