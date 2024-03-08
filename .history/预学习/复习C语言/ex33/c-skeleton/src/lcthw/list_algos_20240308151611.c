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
        LIST_FOREACH(list,first,next,cur){
            if(cmp(cur->value,cur->next->value)>0){
                ListNode_swap(cur,cur->next);
                sorted=0;
            }
        }
    }while(!sorted);
    return 0;
}

inline List *List_merge(List *left,List *right,List_comare cmp){
    List *result=List_create();
    
}