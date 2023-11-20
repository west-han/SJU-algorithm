#include "LinkedList.h"
#include <stdlib.h>

static int _ValidatePosition(List* p_list, int position) {
    if (p_list->numOfData < position - 1 ||
        position <= 0) {
        puts("invalid position");
        return -1;
    }
    return 1;
}

void ListInit(List* p_list) {
    p_list->numOfData = 0;
    p_list->head = (ListNode*)malloc(sizeof(ListNode));
    p_list->trailer = (ListNode*)malloc(sizeof(ListNode));
    p_list->head->next = p_list->trailer;
    p_list->trailer->prev = p_list->head;
}

void Add(List* p_list, int rank, ListElem elem) {
    if (_ValidatePosition(p_list, rank) == -1)
        return;

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    ListNode* target = p_list->head;

    for (int i = 0; i < rank; i++)
        target = target->next;

    newNode->elem = elem;
    newNode->next = target;
    newNode->prev = target->prev;
    (target->prev)->next = newNode;
    target->prev = newNode;

    p_list->numOfData++;
}

ListElem Delete(List* p_list, int rank) {
    if (_ValidatePosition(p_list, rank + 1) == -1)
        return 0;

    ListNode* target = p_list->head;
    ListElem retElem;

    for (int i = 0; i < rank; i++)
        target = target->next;
    retElem = target->elem;

    (target->prev)->next = target->next;
    (target->next)->prev = target->prev;

    free(target);
    p_list->numOfData--;
    return retElem;
}

ListElem Get(const List* p_list, int rank) {
    if (_ValidatePosition(p_list, rank + 1) == -1)
        return -1;

    ListNode* target = p_list->head;
    for (int i = 0; i < rank; i++)
        target = target->next;

    return target->elem;
}

void Print(const List* p_list) {
    ListNode* current = p_list->head->next;

    while (current != p_list->trailer) {
        putchar(current->elem);
        current = current->next;
    }

    putchar('\n');
}