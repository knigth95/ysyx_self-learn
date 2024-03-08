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
    void *val=NULL;
    while(List_count(left)>0 || List_count(right)>0){
        if(List_count(left) > 0 && List_count(right) > 0) {
            if(cmp(List_first(left), List_first(right)) <= 0) {
                val = List_shift(left);
            } else {
                val = List_shift(right);
            }

            List_push(result, val);
        } else if(List_count(left) > 0) {
            val = List_shift(left);
            List_push(result, val);
        } else if(List_count(right) > 0) {
            val = List_shift(right);
            List_push(result, val);
        }
    }
    return result;
}

List *List_merge_sort(List *list,List_comare cmp){
    if(List_count(list)<=1) return list;
    List *left=List_create();
    List *right=List_create();
    int middle=List_count(list)/2;

    LIST_FOREACH(list,first,next,cur){
        if(middle)
    }
}