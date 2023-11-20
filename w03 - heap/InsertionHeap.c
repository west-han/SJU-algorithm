#include "InsertionHeap.h"
#include <stdio.h>

extern int g_heapSize;
extern int g_heapArr[];

int InsertItem(int key) {
    g_heapSize++;
    if (g_heapSize == MAX_LEN)
        return -1;

    g_heapArr[g_heapSize] = key;
    _UpHeap(g_heapSize);

    return 0;
}

void PrintHeap() {
    for (int i = 1; i <= g_heapSize; i++)
        printf(" %d", g_heapArr[i]);
    putchar('\n');
}


int RemoveMax() {
    int key = g_heapArr[1];
    g_heapArr[1] = g_heapArr[g_heapSize--];
    _DownHeap(1);
    return key;
}

static int _GetParentIdx(int idx) {
    return idx / 2;
}

static int _GetLChildIdx(int idx) {
    return idx * 2;
}

static int _GetRChildIdx(int idx) {
    return idx * 2 + 1;
}

static int _IsRoot(int idx) {
    return idx == 1;
}

static void _Swap(int* n1, int* n2) {
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

static void _UpHeap(int idx) {
    int parentIdx = _GetParentIdx(idx);
    while (!_IsRoot(idx) && g_heapArr[parentIdx] < g_heapArr[idx]) {
        _Swap(g_heapArr + parentIdx, g_heapArr + idx);
        idx = parentIdx;
        parentIdx = _GetParentIdx(idx);
    }
}

static int _IsExternal(int idx) {
    return _GetLChildIdx(idx) > g_heapSize;
}

static int _GetHighPriorChildIdx(int idx) {
    int lIdx = _GetLChildIdx(idx);
    int rIdx = _GetRChildIdx(idx);
    if (rIdx > g_heapSize)
        return lIdx;
    return g_heapArr[lIdx] > g_heapArr[rIdx] ? lIdx : rIdx;
}

static void _DownHeap(int idx) {
    int childIdx = _GetHighPriorChildIdx(idx);
    while (!_IsExternal(idx) && g_heapArr[idx] < g_heapArr[childIdx]) {
        _Swap(g_heapArr + idx, g_heapArr + childIdx);
        idx = childIdx;
        childIdx = _GetHighPriorChildIdx(idx);
    }
}