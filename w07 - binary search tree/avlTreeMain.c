//#pragma warning(disable:4996)
//#include "AVL_Tree.h"
//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//    char c;
//    Node* root = (Node*)calloc(1, sizeof(Node));
//
//    while((c = getchar()) != 'q')
//    {
//        switch(c)
//        {
//            int key;
//            int outKey;
//            
//            case 'i':
//                scanf("%d", &key);
//                getchar();
//                insertItem(&root, key);
//                break;
//            
//            case 's':
//            {
//                scanf("%d", &key);
//                getchar();
//                if(findElement(root, key, &outKey))
//                {
//                    printf("%d\n", outKey);
//                }
//                else
//                {
//                    puts("X");
//                }
//                break;
//            }
//
//            case 'd':
//            {
//                scanf("%d", &key);
//                getchar();
//                if(removeElement(&root, key, &outKey))
//                {
//                    printf("%d\n", outKey);
//                }
//                else
//                {
//                    puts("X");
//                }
//                break;
//            }
//            case 'p':
//                preOrderPrintTree(root);
//                putchar('\n');
//        }
//    }
//
//    return 0;
//}