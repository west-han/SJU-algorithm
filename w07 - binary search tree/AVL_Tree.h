#pragma once

typedef struct _node{
    int key;
    int height;
    struct _node* lChild;
    struct _node* rChild;
    struct _node* parent;
} Node;

void expandExternal(Node* node);
Node* reduceExternal(Node** p_root, Node* node);
Node* restructure(Node** p_root, Node* x, Node* y, Node* z);
Node* treeSearch(Node* root, const int key);
_Bool findElement(Node* root, const int key, int* outParam);
Node* findInOrderSucc(const Node* node);
_Bool insertItem(Node** p_root, const int key);
void preOrderPrintTree(Node* root);
_Bool removeElement(Node** p_root, const int key, int* outParam);