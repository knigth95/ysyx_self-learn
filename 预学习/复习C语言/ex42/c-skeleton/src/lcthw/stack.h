#ifndef _Stack_h
#define _Stack_h

#include <stdlib.h>

typedef struct StackNode {
    void *data;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
    int count;
} Stack;

// 创建栈
Stack* Stack_create() {
    Stack *stack = malloc(sizeof(Stack));
    stack->top = NULL;
    stack->count = 0;
    return stack;
}

// 销毁栈
void Stack_destroy(Stack *stack) {
    StackNode *current = stack->top;
    StackNode *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(stack);
}

// 推入栈
void Stack_push(Stack *stack, void *data) {
    StackNode *node = malloc(sizeof(StackNode));
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->count++;
}

// 弹出栈
void* Stack_pop(Stack *stack) {
    if (stack->top == NULL) {
        return NULL;
    }

    StackNode *node = stack->top;
    void *data = node->data;
    stack->top = node->next;
    free(node);
    stack->count--;
    return data;
}

// 查看栈顶元素
void* Stack_peek(Stack *stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    return stack->top->data;
}

// 获取栈的元素数量
int Stack_count(Stack *stack) {
    return stack->count;
}

#define STACK_FOREACH(stack,cur) \
    for(StackNode *cur = (stack)->top;cur!=NULL;cur=cur->next)

#endif
