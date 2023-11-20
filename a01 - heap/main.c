#include "FindKthSmallest.h"
#include "Heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int main(){
    srand(time(NULL));
    LARGE_INTEGER ticksPerSecond, start, end, diff;
    double time = 0.0;

    const int n1 = 10;
    const int n2 = 100000;
    const int* randArr1 = buildList(n1, 1, 100);
    const int* randArr2;
    const int kArray[4] = { 1, 100, 99900, 99999 };
    int* p_buffer = NULL;
    int kthMin = 0;

    for (int i = 0; i < 10; i++)
        printf(" %d", randArr1[i + 1]);
    putchar('\n');

    for (int i = 0; i < 3; i++) {
        p_buffer = allocAndCopyArr(randArr1, p_buffer, n1);

        printf(" %d", findKthSmallest(p_buffer, n1, i + 1));
        
        free(p_buffer);
        p_buffer = NULL;
    }
    
    randArr2 = buildList(n2, 1, 1000000);

    for (int i = 0; i < 4; i++) {
        p_buffer = allocAndCopyArr(randArr2, p_buffer, n2);

        QueryPerformanceFrequency(&ticksPerSecond);
        QueryPerformanceCounter(&start);
        kthMin = findKthSmallest(p_buffer, n2, kArray[i]);
        QueryPerformanceCounter(&end);
        
        diff.QuadPart = end.QuadPart - start.QuadPart;
        time = ((double)diff.QuadPart / (double)ticksPerSecond.QuadPart);

        printf("\n%dth_min: %d\ttime: %lf", kArray[i], kthMin, time);

        free(p_buffer);
        p_buffer = NULL;
    }

    return 0;
}