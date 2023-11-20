#include <stdio.h>

#define MAX_LEN     100

int g_heapArr[MAX_LEN] = { 0, };
int g_heapSize = 0;

void RBuildHeap(int idx);
void PrintHeap();
void BuildHeap();