//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <malloc.h>
//#include "BinaryTree.h"
//
//int main(void) {
//    int num;
//    int parent, left, right;
//    char searchInfo[101];
//    scanf("%d", &num);
//    BTNode* root = CreateNode();
//
//    scanf("%d %d %d", &parent, &left, &right);
//    SetData(root, parent);
//    InsertNode(root, parent, left, right);
//    for (int i = 0; i < num - 1; ++i) {
//        scanf("%d %d %d", &parent, &left, &right);
//        InsertNode(root, parent, left, right);
//    }
//
//    scanf("%d", &num);
//    getchar();
//    for (int i = 0; i < num; i++) {
//        gets(searchInfo);
//        SearchTree(root, searchInfo);
//        printf("\n");
//    }
//
//    return 0;
//}
