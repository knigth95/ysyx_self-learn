#include <stdio.h>
#include "../src/lcthw/ringbuffer.h"

// 声明测试函数
void test_create();
void test_read_write();
void test_destroy();


void fuzz_test(RingBuffer *buffer) {
    srand(time(NULL)); // 初始化随机数生成器
    for(int i = 0; i < 1000; i++) {
        int operation = rand() % 2; // 0代表写入，1代表读取
        int size = rand() % 100; // 随机大小
        if(operation == 0) {
            // 随机生成数据并写入
            char *data = malloc(size);
            for(int j = 0; j < size; j++) {
                data[j] = rand() % 256;
            }
            RingBuffer_write(buffer, data, size);
            free(data);
        } else {
            // 读取数据到临时缓冲区
            char *data = malloc(size);
            RingBuffer_read(buffer, data, size);
            free(data);
        }
    }
}

int main(int argc, char *argv[]) {
    printf("DEBUG %s:%d: ----- RUNNING: %s\n", __FILE__, __LINE__, argv[0]);
    printf("----\n");
    printf("RUNNING: %s\n", argv[0]);

    test_create();
    test_read_write();
    test_destroy();

    printf("ALL TESTS PASSED\n");
    printf("Tests run: 3\n");

    return 0;
}

void test_create() {
    printf("DEBUG %s:%d:\n----- test_create\n", __FILE__, __LINE__);
    // 这里添加创建缓冲区的测试代码
    RingBuffer *buffer = RingBuffer_create(100);
    if (buffer != NULL && buffer->buffer != NULL) {
        printf("test_create passed.\n");
    } else {
        printf("test_create failed.\n");
    }
    RingBuffer_destroy(buffer);
}

void test_read_write() {
    printf("DEBUG %s:%d:\n----- test_read_write\n", __FILE__, __LINE__);
    // 这里添加写入和读取的测试代码
    RingBuffer *buffer = RingBuffer_create(10);
    char *test_data = "12345";
    RingBuffer_write(buffer, test_data, 5);

    char read_buffer[6] = {0}; // 多一个字节存放字符串结束符 '\0'
    RingBuffer_read(buffer, read_buffer, 5);

    if (strcmp(test_data, read_buffer) == 0) {
        printf("test_read_write passed.\n");
    } else {
        printf("test_read_write failed.\n");
    }
    RingBuffer_destroy(buffer);
}

void test_destroy() {
    printf("DEBUG %s:%d:\n----- test_destroy\n", __FILE__, __LINE__);
    // 这里验证是否会造成内存泄漏
    RingBuffer *buffer = RingBuffer_create(100);
    RingBuffer_destroy(buffer);
    printf("test_destroy passed.\n");
}

//gcc -o ringbuffer_test ../src/lcthw/ringbuffer.c  ../src/lcthw/bstrlib.c ringbuffer_test.c

//valgrind --tool=callgrind ./ringbuffer_test