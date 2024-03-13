#include "ringbuffer_posix.h"
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

// 创建一个环形缓冲区
RingBuffer *RingBuffer_create(int length) {
    int fd = -1;
    RingBuffer *buffer = malloc(sizeof(RingBuffer));
    if (!buffer) return NULL;

    buffer->length = length + 1; // 留一个空位判断满
    buffer->start = 0;
    buffer->end = 0;

    // 使用匿名映射来创建缓冲区
    fd = open("/dev/zero", O_RDWR);
    buffer->buffer = mmap(NULL, buffer->length, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);

    if (buffer->buffer == MAP_FAILED) {
        free(buffer);
        return NULL;
    }

    return buffer;
}

void RingBuffer_destroy(RingBuffer *buffer) {
    if (buffer) {
        munmap(buffer->buffer, buffer->length);
        free(buffer);
    }
}

int RingBuffer_write(RingBuffer *buffer, const char *data, int length) {
    if (RingBuffer_available_space(buffer) < length) {
        // Not enough space
        return -1;
    }

    void *result = memcpy(buffer->buffer + buffer->end, data, length);
    if (result == NULL) {
        // Failed to write data
        return -1;
    }

    // Move end forward and wrap around if necessary
    buffer->end = (buffer->end + length) % buffer->length;
    if (buffer->end >= buffer->length) {
        buffer->end -= buffer->length;
    }

    return length;
}

int RingBuffer_read(RingBuffer *buffer, char *target, int amount) {
    if (RingBuffer_available_data(buffer) < amount) {
        // Not enough data
        return -1;
    }

    void *result = memcpy(target, buffer->buffer + buffer->start, amount);
    if (result == NULL) {
        // Failed to read data
        return -1;
    }

    // Move start forward and wrap around if necessary
    buffer->start = (buffer->start + amount) % buffer->length;
    if (buffer->start >= buffer->length) {
        buffer->start -= buffer->length;
    }

    return amount;
}

int RingBuffer_available_data(const RingBuffer *buffer) {
    if (buffer->end >= buffer->start) {
        return buffer->end - buffer->start;
    } else {
        return buffer->length - buffer->start + buffer->end;
    }
}

int RingBuffer_available_space(const RingBuffer *buffer) {
    return buffer->length - RingBuffer_available_data(buffer) - 1;
}