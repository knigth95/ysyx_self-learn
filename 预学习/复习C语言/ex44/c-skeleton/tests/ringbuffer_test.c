#include "../src/lcthw/ringbuffer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_create_destroy() {
    printf("Test: Create and Destroy\n");
    RingBuffer *buffer = RingBuffer_create(10);
    assert(buffer != NULL);
    assert(buffer->length == 11); // 包括一个未使用的字节来区分满和空
    RingBuffer_destroy(buffer);
    printf("PASS: Create and Destroy\n\n");
}

void test_read_write() {
    printf("Test: Read and Write\n");
    RingBuffer *buffer = RingBuffer_create(10);
    char *data = "12345";
    int write_result = RingBuffer_write(buffer, data, strlen(data));
    assert(write_result == strlen(data));
    assert(RingBuffer_available_data(buffer) == strlen(data));

    char target[6] = {0};
    int read_result = RingBuffer_read(buffer, target, strlen(data));
    assert(read_result == strlen(data));
    assert(strcmp(data, target) == 0);
    assert(RingBuffer_empty(buffer));

    RingBuffer_destroy(buffer);
    printf("PASS: Read and Write\n\n");
}

void test_overflow() {
    printf("Test: Overflow\n");
    RingBuffer *buffer = RingBuffer_create(5);
    char *data = "123456";
    int result = RingBuffer_write(buffer, data, strlen(data));
    assert(result == -1); // 写入失败，因为数据长度超出缓冲区容量
    RingBuffer_destroy(buffer);
    printf("PASS: Overflow\n\n");
}

void test_wrap_around() {
    printf("Test: Wrap Around\n");
    RingBuffer *buffer = RingBuffer_create(5);
    char *data = "123";
    RingBuffer_write(buffer, data, strlen(data));
    char target[4] = {0};
    RingBuffer_read(buffer, target, 2); // 读取部分数据，使start向前移动

    char *more_data = "45";
    RingBuffer_write(buffer, more_data, strlen(more_data)); // 写入更多数据，测试环绕

    assert(RingBuffer_available_data(buffer) == 4);
    RingBuffer_read(buffer, target, 4); // 尝试读取所有数据
    assert(strcmp(target, "345") == 0); // 只比较有效数据部分

    RingBuffer_destroy(buffer);
    printf("PASS: Wrap Around\n\n");
}

int main() {
    test_create_destroy();
    test_read_write();
    test_overflow();
    test_wrap_around();
    printf("All tests passed.\n");
    return 0;
}
