#ifndef _Queue_h
#define _Queue_h

#include <stdlib.h>

typedef struct QueueNode {
    void *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *first;
    QueueNode *last;
    int count;
} Queue;

// 创建队列
Queue* Queue_create() {
    Queue *queue = malloc(sizeof(Queue));
    queue->first = NULL;
    queue->last = NULL;
    queue->count = 0;
    return queue;
}

// 销毁队列
void Queue_destroy(Queue *queue) {
    QueueNode *current = queue->first;
    QueueNode *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(queue);
}

// 添加元素到队列
void Queue_send(Queue *queue, void *data) {
    QueueNode *node = malloc(sizeof(QueueNode));
    node->data = data;
    node->next = NULL;

    if (queue->last != NULL) {
        queue->last->next = node;
    }
    queue->last = node;

    if (queue->first == NULL) {
        queue->first = node;
    }

    queue->count++;
}

// 从队列移除元素
void* Queue_recv(Queue *queue) {
    if (queue->first == NULL) {
        return NULL;
    }

    QueueNode *node = queue->first;
    void *data = node->data;
    queue->first = node->next;
    
    if (queue->first == NULL) {
        queue->last = NULL; // 队列为空时重置last指针
    }

    free(node);
    queue->count--;
    return data;
}

// 查看队列首元素
void* Queue_peek(Queue *queue) {
    if (queue->first == NULL) {
        return NULL;
    }
    return queue->first->data;
}

// 获取队列的元素数量
int Queue_count(Queue *queue) {
    return queue->count;
}

#define QUEUE_FOREACH(queue, cur) \
    for(QueueNode *cur = (queue)->first; cur != NULL; cur = cur->next)

#endif
