#include"list_algos.h"
#include"dbg.h"

inline void ListNode_swap(ListNode *a,ListNode *b){
    void *temp=a->value;
    a->value=b->value;
    b->value=temp;
}

int List_bubble_sort(List *list,List_comare cmp){
    int sorted=1;
    if(List_count(list)<=1) return 0;
    do{
        sorted=1;
        LIST_FOREACH(list,first,next,cur)
    }
}