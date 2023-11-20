#pragma warning(disable:4996)
#include <stdio.h>
#include <malloc.h>
#include "LinkedList.h"

int main(void) {
    int n, rank;
    char opType;
    ListElem data;

    scanf("%d", &n);
    getchar();
    List list;
    ListInit(&list);

    for (int i = 0; i < n; i++) {
        scanf("%c", &opType);

        switch (opType) {
        case 'A':
            scanf("%d %c", &rank, &data);
            Add(&list, rank, data);
            break;
        case 'D':
            scanf("%d", &rank);
            Delete(&list, rank);
            break;
        case 'G':
            scanf("%d", &rank);
            if ((data = Get(&list, rank)) != -1)
                printf("%c\n", data);
            break;
        case 'P':
            Print(&list);
            break;
        }
        getchar();
    }

    return 0;
}
