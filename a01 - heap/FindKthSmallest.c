#include <stdio.h>
#include "FindKthSmallest.h"
#include "Heap.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *buildList(int n, int min, int max){
    int* retArr = (int*)malloc(sizeof(int) * (n+1));
    retArr[0] = 0;
    
    for (int i = 1; i <= n; ++i)
        retArr[i] = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;

    return retArr;
}

int findKthSmallest(int *L, int n, int k){
    int retKey = 0;

    buildHeap(L, n);

    for(int i = 0; i < k; i++){
        retKey = removeMin(L, &n);
    }

    return retKey;
}

int* allocAndCopyArr(const int* src, int* p_dest, int numElem){
    unsigned long long size = sizeof(int) * (unsigned long long)(numElem + 1);
    p_dest = (int*)malloc(sizeof(int) * size);
    memcpy(p_dest, src, size);
    return p_dest;
}