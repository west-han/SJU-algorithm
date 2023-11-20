#include "BottomUpHeap.h"

void PrintHeap() {
    for (int i = 1; i <= g_heapSize; i++)
        printf(" %d", g_heapArr[i]);
    putchar('\n');
}

static int _GetLChildIdx(int idx) {
    return idx * 2;
}

static int _GetRChildIdx(int idx) {
    return idx * 2 + 1;
}

static void _Swap(int* n1, int* n2) {
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
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

void RBuildHeap(int idx) {
    if (!_IsExternal(idx)) {
        RBuildHeap(_GetLChildIdx(idx));
        RBuildHeap(_GetRChildIdx(idx));
        _DownHeap(idx);
    }
}

void BuildHeap() {
    for (int i = g_heapSize / 2; i >= 1; i--)
        _DownHeap(i);
}