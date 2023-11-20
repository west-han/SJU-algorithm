#include "BinaryTree.h"
#include <stdlib.h>

BTNode* CreateNode() {
    BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void SetData(BTNode* p_node, BTData data) {
    p_node->data = data;
}

void AddLChild(BTNode* p_parent, BTNode* p_child) {
    p_parent->left = p_child;
}

void AddRChild(BTNode* p_parent, BTNode* p_child) {
    p_parent->right = p_child;
}

void _PreOrderFindNodeLoc(const BTNode* p_bt, BTData parentData, BTNode** pp_output) {
    if (p_bt == NULL || (*pp_output)->data == parentData)
        return;
    if (p_bt->data == parentData) {
        *pp_output = p_bt;
        return;
    }

    _PreOrderFindNodeLoc(p_bt->left, parentData, pp_output);
    _PreOrderFindNodeLoc(p_bt->right, parentData, pp_output);
}

void InsertNode(const BTNode* p_root, BTData parentData, BTData leftData, BTData rightData) {
    BTNode* parent = p_root;
    _PreOrderFindNodeLoc(p_root, parentData, &parent);
    if (leftData != 0) {
        BTNode* leftChild = CreateNode();
        SetData(leftChild, leftData);
        AddLChild(parent, leftChild);
    }
    if (rightData != 0) {
        BTNode* rightChild = CreateNode();
        SetData(rightChild, rightData);
        AddRChild(parent, rightChild);
    }
}

void SearchTree(BTNode* p_bt, const char* searchTargets) {
    if (p_bt == NULL)
        return;
    printf(" %d", p_bt->data);

    if (*searchTargets == 'R') {
        SearchTree(p_bt->right, searchTargets + 1);
    }
    else if (*searchTargets == 'L')
        SearchTree(p_bt->left, searchTargets + 1);
}
