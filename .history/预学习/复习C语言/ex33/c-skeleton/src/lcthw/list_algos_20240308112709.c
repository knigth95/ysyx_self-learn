#include"list_algos.h"
#include"dbg.h"

inline void ListNode_swap(ListNode *a,ListNode *b){
    void *temp=a->value;
    a->value=b->value;
    b->value=temp;
}

int List_bubble