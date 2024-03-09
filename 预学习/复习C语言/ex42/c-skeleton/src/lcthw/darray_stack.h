#ifndef _darray_stack_h
#define _darray_stack_h

#include "stack.h"

typedef DArray Stack;

// 创建栈
#define Stack_create() (DArray_create(sizeof(void *), 100))

// 销毁栈
#define Stack_destroy(stack) (DArray_destroy(stack))

// 推入栈
#define Stack_push(stack, value) (DArray_push(stack, value))

// 弹出栈
#define Stack_pop(stack) (DArray_pop(stack))

// 查看栈顶元素
void *Stack_peek(const Stack *stack) {
    return DArray_last(stack);
}

// 获取栈的元素数量
#define Stack_count(stack) (DArray_count(stack))

// 遍历栈
#define STACK_FOREACH(stack, cur) \
    for(int _i = DArray_count(stack) - 1; _i >= 0; _i--) \
    for(cur = DArray_get(stack, _i); _i >= 0; _i = -2)

#endif
