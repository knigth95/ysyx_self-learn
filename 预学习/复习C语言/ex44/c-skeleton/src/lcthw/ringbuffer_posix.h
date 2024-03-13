#ifndef _RINGBUFFER_POSIX_H
#define _RINGBUFFER_POSIX_H

typedef struct {
    char *buffer;
    int length;
    int start;
    int end;
} RingBuffer;

RingBuffer *RingBuffer_create(int length);
void RingBuffer_destroy(RingBuffer *buffer);
int RingBuffer_write(RingBuffer *buffer, const char *data, int length);
int RingBuffer_read(RingBuffer *buffer, char *target, int amount);

#endif