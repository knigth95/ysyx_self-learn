#include "list.h"
#include "dbg.h"

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
        if(cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}


void List_clear(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
        if(cur->value){
            free(cur->value);
            cur->value=NULL;//防止悬挂
        }
    }
}


void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}

void List_push(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(List *list)
{
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List *list)
{
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if(node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}

List *List_copy(List *list) {
    assert(list != NULL);
    List *new_list = List_create();
    LIST_FOREACH(list, first, next, cur) {
        List_push(new_list, cur->value);
    }
    return new_list;
}
void List_join(List *list1, List *list2) {
    assert(list1 != NULL && list2 != NULL);

    LIST_FOREACH(list2, first, next, cur) {
        List_push(list1, cur->value); // 假设List_push已经实现
    }
}

List *List_split(List *list, int position) {
    assert(list != NULL && position >= 0);
    List *new_list = List_create();
    int index = 0;

    ListNode *node = list->first;
    while (node != NULL && index < position) {
        node = node->next;
        index++;
    }
    // 从当前位置分割链表
    if (node != NULL) {
        new_list->first = node;
        new_list->last = list->last;
        list->last = node->prev;
        list->last->next = NULL;
        node->prev = NULL;
    }

    // 更新计数
    new_list->count = position;
    list->count -= position;

    return new_list;
}
void List_reverse(List *list) {
    assert(list != NULL);
    ListNode *current = list->first;
    ListNode *prev = NULL, *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }
    // 交换首尾指针
    current = list->first;
    list->first = list->last;
    list->last = current;
}
