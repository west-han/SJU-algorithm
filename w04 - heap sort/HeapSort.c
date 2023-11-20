#include "HeapSort.h"
#include <stdio.h>

// helper function prototypes
static int _IsRoot(int idx);
static int _IsExternal(int idx);
static int _IsInternal(int idx);
static int _GetLChildIdx(int idx);
static int _GetRChildIdx(int idx);
static int _GetParentIdx(int idx);
static int _GetHighPriorChildIdx(int idx);
static int _Swap(int* n1, int* n2);

// ADTs
void inPlaceHeapSort() {
    g_heapSize = g_n;
    for (int i = g_heapSize; i > 1; i--) { // phase 2
        g_n--;
        _Swap(g_H + 1, g_H + i);
        downHeap(1);
    }
}

void printArray() {
    for (int i = 1; i <= g_heapSize; i++)
        printf(" %d", g_H[i]);
}

void downHeap(int i) {
    int childIdx = _GetHighPriorChildIdx(i);
    while (_IsInternal(i) && g_H[childIdx] > g_H[i]) {
        _Swap(g_H + i, g_H + childIdx);
        i = childIdx;
        childIdx = _GetHighPriorChildIdx(i);
    }
}

void insertItem(int key) {
    g_H[++g_n] = key;
    upHeap(g_n);
}

void upHeap(int i) {
    int parentIdx = _GetParentIdx(i);
    while (!_IsRoot(i) && g_H[i] > g_H[parentIdx]) {
        _Swap(g_H + i, g_H + parentIdx);
        i = parentIdx;
        parentIdx = _GetParentIdx(i);
    }
}

void rBuildHeap(int i) {
    if (_IsInternal(i)) {
        rBuildHeap(_GetLChildIdx(i));
        rBuildHeap(_GetRChildIdx(i));
        downHeap(i);
    }
}

void buildHeap() {
    int last = _GetParentIdx(g_n);
    for (int i = last; i >= 1; i--)
        downHeap(i);
}


// helper function definitions
int _IsRoot(int idx) {
    return idx == 1;
}

static int _IsExternal(int idx) {
    return g_n < _GetLChildIdx(idx);
}

static int _IsInternal(int idx) {
    return !_IsExternal(idx);
}

static int _GetLChildIdx(int idx) {
    return idx * 2;
}

static int _GetRChildIdx(int idx) {
    return idx * 2 + 1;
}

static int _GetParentIdx(int idx) {
    return idx / 2;
}

static int _GetHighPriorChildIdx(int idx) {
    int lIdx = _GetLChildIdx(idx);
    int rIdx = _GetRChildIdx(idx);
    if (rIdx > g_n)
        return lIdx;

    return g_H[lIdx] > g_H[rIdx] ? lIdx : rIdx;
}

int _Swap(int* n1, int* n2) {
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}