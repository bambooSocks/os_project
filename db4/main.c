#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main() {
    int counter = 0;
    linked_list_t *ll = newLL();
    int isRunning = 1;

    while (isRunning) {
        char ch = fgetc(stdin);
        switch (ch) {
        case 'a':
            pushToLL(ll, counter);
            counter++;
            break;
        case 'b':
            counter++;
            break;
        case 'c':
            popFromLL(ll, NULL);
            counter++;
            break;
        default:
            printLL(ll);
            isRunning = 0;
        }
    }

    return 0;
}


