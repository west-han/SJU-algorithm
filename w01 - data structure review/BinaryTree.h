#pragma once

typedef struct _bTreeNode BTNode;
typedef int BTData;

struct _bTreeNode {
    BTData data;
    BTNode* left;
    BTNode* right;
};

BTNode* CreateNode();
void SetData(BTNode* p_node, BTData data);
void AddLChild(BTNode* p_parent, BTNode* p_child);
void AddRChild(BTNode* p_parent, BTNode* p_child);
void InsertNode(const BTNode* root, BTData parentData, BTData leftData, BTData rightData);
void SearchTree(BTNode* p_bt, const char* searchTargets);
