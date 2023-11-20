#include <stdio.h>
#include "InsertionHeap.h"

int main() {
    char command;
    int key;

    while ((command = getchar()) != 'q') {
        switch (command) {
        case 'i':
            scanf("%d", &key);
            printf("%d\n", InsertItem(key));
            getchar();
            break;

        case 'd':
            printf("%d\n", RemoveMax());
            break;

        case 'p':
            PrintHeap();
            break;
        }
    }
}