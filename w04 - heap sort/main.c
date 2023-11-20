#include <stdio.h>
#include "HeapSort.h"

extern int g_H[];
extern int g_n;
extern int g_heapSize;

/* test samples
 * 8 5 15 10 20 30 25 31 29
 * 6 24 17 33 50 60 70
 * 3 209 400 77
 */

int main() {
    int n, key;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        insertItem(key);
    }

    inPlaceHeapSort();
    printArray();
}