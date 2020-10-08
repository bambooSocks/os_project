#include "linkedlist.h"
#include "io.h"

// Linked lists have to be created using the function in order to ensure that they
// are intitialzied correctly
linked_list_t* newLL() {
    linked_list_t* ll = (linked_list_t*) malloc(sizeof(linked_list_t));
    ll->size = 0;
    ll->data = NULL;
    return ll;
}

// Push a value to the Linked list (ll).
// Returns LL_SUCCESS if the value was added successfully
// If there is not enough memory the function returns LL_ALLOCATION_ERROR
LL_RETURN_t pushToLL(linked_list_t* ll, int value) {

    // get the first node's pointer's address
    ll_node_t** last_node = &(ll->data);

    // propagate through the pointers to find a node which next 
    // pointer points to NULL (last node)
    if (*last_node != NULL) {
        last_node = &((*last_node)->next);
        while (*last_node != NULL) {
            last_node = &((*last_node)->next);
        }
    }

    // allocate space for new node that the last_node will point to
    *last_node = (ll_node_t*) malloc(sizeof(ll_node_t));
    if (*last_node == NULL) {
        char *msg = "Couldn't allocate memory for new node\n";
        syscall_write(msg, strlen(msg));
        return LL_ALLOCATION_ERROR;
    }

    // put new data into the new node
    (*last_node)->value = value;
    (*last_node)->next = NULL;
    return LL_SUCCESS;
}

// Pops a value from the Linked list (ll) and puts it into passed variable
// ret_val has to be an address to an existing integer variable 
// or NULL when it should be ignored
// Returns LL_SUCCESS if the value was popped successfully
// If the list is empty the function returns LL_OUT_OF_DATA_ERROR
LL_RETURN_t popFromLL(linked_list_t* ll, int* ret_val) {
    // get the first node's pointer's address
    ll_node_t** last_node = &(ll->data);
    
    // list is empty
    if (*last_node == NULL) {
        return LL_OUT_OF_DATA_ERROR;
    }

    // check whether the list doesn't contain only one node
    if ((*last_node)->next != NULL) {
        // find a second to last node
        while ((*last_node)->next->next != NULL) {
            last_node = &((*last_node)->next);
        }
    }

    // write the value if the pointer is not NULL
    if (ret_val != NULL)
        *ret_val = (*last_node)->next->value;

    // free the memory and remove reference to the node
    free((*last_node)->next);
    (*last_node)->next = NULL;

    return LL_SUCCESS;
}

// Prints the Linked list (ll)
void printLL(linked_list_t* ll) {
    ll_node_t* last_node = ll->data;
    if (last_node != NULL) {
        write_int(last_node->value);
        while (last_node->next != NULL) {
            last_node = last_node->next;
            syscall_write(", ", 2);
            write_int(last_node->value);
        }
    }
    syscall_write("\n", 1);
}



