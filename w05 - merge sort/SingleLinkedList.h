#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct _listNode{
    int data;
    struct _listNode* next;
} LNode;

typedef struct _list{
    LNode* head;
    int numOfData;
} List;

inline void LInit(List* p_list)
{
    p_list->head = (LNode*)malloc(sizeof(LNode));
    p_list->head->next = NULL;
    p_list->numOfData = 0;
}


inline void LInsertLast(List* p_list, int data)
{
    LNode* beforeNewNode = p_list->head;
    LNode* newNode = (LNode*)malloc(sizeof(LNode));

    for (int i = 0; i < p_list->numOfData; i++) {
        beforeNewNode = beforeNewNode->next;
    }

    newNode->data = data;
    newNode->next = beforeNewNode->next;
    beforeNewNode->next = newNode;
    p_list->numOfData += 1;
}

inline int LRemoveFirst(List* p_list)
{
    if (LIsEmpty(p_list)) {
        puts("List Underflow");
        exit(-1);
    }

    LNode* delNode = p_list->head->next;
    int retData = delNode->data;

    p_list->head->next = delNode->next;
    p_list->numOfData -= 1;

    free(delNode);
    return retData;
}

inline int LIsEmpty(List* p_list){
    return p_list->numOfData == 0;
}

inline int LGetFirst(List* p_list){
    return p_list->head->next->data;
}

inline int LDiscardList(List* p_list) {
    while (!LIsEmpty(p_list)) {
        printf(" %d", LRemoveFirst(p_list));
    }
    free(p_list->head);
    p_list->head = NULL;
}
