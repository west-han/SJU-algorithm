#pragma once

#define HEAP_LEN    100

int g_H[HEAP_LEN] = { 0, };
int g_n = 0;
int g_heapSize = 0;

void inPlaceHeapSort();
void printArray();
void downHeap(int i);
void insertItem(int key);
void upHeap(int i);
void rBuildHeap(int i);
void buildHeap();