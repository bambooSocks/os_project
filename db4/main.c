#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "io.h"

int main() {
    int counter = 0;
    linked_list_t *ll = newLL();
    int isRunning = 1;

    int num = -10;
    printf("\n%d\n", write_int(num));


    while (isRunning) {
        char ch;
        syscall_read(&ch, 1);
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


