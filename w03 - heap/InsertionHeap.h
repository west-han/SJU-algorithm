#pragma once

#define MAX_LEN     100

int g_heapArr[MAX_LEN] = { 0, };
int g_heapSize = 0;

int InsertItem(int key);
int RemoveMax();
void PrintHeap();
