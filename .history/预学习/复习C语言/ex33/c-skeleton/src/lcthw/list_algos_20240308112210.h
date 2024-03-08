#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include "list.h"

typedef int (*List_comare)(const void *a,const void *b);

int List_bubble_sort(List *list,List_comare cmp);

List *List_merge_sort(List *list,List_comare cmp);
#