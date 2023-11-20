//#include "ListMergeSort.h"
//
//static void partition(List* p_list, List* p_out_L1, List* p_out_L2, int k){
//    for(int i = 0; i < k; i++){
//        LInsertLast(p_out_L1, LRemoveFirst(p_list));
//    }
//    while(p_list->numOfData!=0){
//        LInsertLast(p_out_L2, LRemoveFirst(p_list));
//    }
//}
//
//static void merge(List* p_out_list, List* p_L1, List* p_L2){
//    while(!LIsEmpty(p_L1) && !LIsEmpty(p_L2)){
//        if(LGetFirst(p_L1) < LGetFirst(p_L2)){
//            LInsertLast(p_out_list, LRemoveFirst(p_L1));
//        }
//        else{
//            LInsertLast(p_out_list, LRemoveFirst(p_L2));
//        }
//    }
//
//    while(!LIsEmpty(p_L1)){
//        LInsertLast(p_out_list, LRemoveFirst(p_L1));
//    }
//
//    while(!LIsEmpty(p_L2)){
//        LInsertLast(p_out_list, LRemoveFirst(p_L2));
//    }
//}
//
//void mergeSort(List *p_list)
//{
//    List L1, L2;
//    LInit(&L1);
//    LInit(&L2);
//
//    if(p_list->numOfData > 1){
//        partition(p_list, &L1, &L2, p_list->numOfData / 2);
//        mergeSort(&L1);
//        mergeSort(&L2);
//        merge(p_list, &L1, &L2);
//    }
//}
