//#include <stdio.h>
//#include "BinarySearchTree.h"
//
//extern Node* g_root;
//
//int main()
//{
//    initBST(&g_root);
//    
//    char c;
//    while((c = getchar()) && (c != 'q')){
//        switch(c){
//            int key;
//            case 'i':
//                scanf("%d", &key);
//                getchar();
//                insertItem(g_root, key);
//                break;
//            case 'p':
//                preOrderTraversal(g_root);
//                putchar('\n');
//                break;
//            case 's':
//                scanf("%d", &key);
//                getchar();
//                if((key = findElement(g_root, key)) != -1){
//                    printf("%d\n", key);
//                }
//                break;
//            case 'd':
//                scanf("%d", &key);
//                getchar();
//                if((key = removeElement(g_root, key)) != -1){
//                    printf("%d\n", key);
//                }
//                break;
//        }
//    }
//}