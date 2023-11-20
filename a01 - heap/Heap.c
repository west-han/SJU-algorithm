#include "Heap.h"
#include <stdio.h>
#include <stdlib.h>

static inline int _GetParentIdx(const int idx){
    return idx / 2;
}

static inline int _GetLChildIdx(const int idx){
    return idx * 2;
}

static inline int _GetRChildIdx(const int idx){
    return idx * 2 + 1;
}

static inline int _GetHighPriorChildIdx(const int arr[], const int idx, const int lastIdx){
    int retIdx = _GetLChildIdx(idx);
    int rIdx = _GetRChildIdx(idx);
    
    if(lastIdx < rIdx)
        return retIdx;
    
    else if(arr[retIdx] > arr[rIdx])
        retIdx = rIdx;
    
    return retIdx;
}

static inline int _IsInternal(const int idx, const int lastIdx){
    return _GetLChildIdx(idx) <= lastIdx;
}

static inline void _Swap(int* n1, int* n2){
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

static void _DownHeap(int arr[], int idx, const int lastIdx){
    int childIdx = _GetHighPriorChildIdx(arr, idx, lastIdx);

    while(_IsInternal(idx, lastIdx) && arr[idx] > arr[childIdx]){
        _Swap(arr+idx, arr+childIdx);
        idx = childIdx;
        childIdx = _GetHighPriorChildIdx(arr, idx, lastIdx);
    }
}

void buildHeap(int arr[], const int lastIdx){
    int idx = _GetParentIdx(lastIdx);
    for(int i = idx; i > 0; i--)
      _DownHeap(arr, i, lastIdx);
}

int removeMin(int arr[], int* const p_lastIdx){
    if(*p_lastIdx <= 0)
        exit(-1);
    int retKey = arr[1];

    arr[1] = arr[*p_lastIdx];
    *p_lastIdx -= 1;
    _DownHeap(arr, 1, *p_lastIdx);
    
    return retKey;
}