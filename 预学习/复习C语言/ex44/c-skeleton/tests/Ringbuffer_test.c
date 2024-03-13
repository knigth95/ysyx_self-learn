#include "minunit.h"
#include "../src/lcthw/ringbuffer.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

static RingBuffer *buffer = NULL;
const int max_buffer_size = 4096;
const char *test_messages[] = {"Hello world", "Ring buffer test", "Last message"};
const int num_messages = sizeof(test_messages) / sizeof(test_messages[0]);

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

char *test_create() {
    buffer = RingBuffer_create(max_buffer_size);
    mu_assert(buffer != NULL, "Failed to create ring buffer.");
    mu_assert(buffer->length == max_buffer_size + 1, "Incorrect buffer length.");
    mu_assert(buffer->start == 0 && buffer->end == 0, "Buffer start and end should initially be 0.");
    return NULL;
}

char *test_write_read() {
    // Write messages to the buffer and then read them back to verify correctness
    char read_buffer[max_buffer_size];
    for (int i = 0; i < num_messages; i++) {
        memset(read_buffer, 0, max_buffer_size);  // Reset read buffer
        int message_len = strlen(test_messages[i]);
        
        // Write and then immediately read
        mu_assert(RingBuffer_write(buffer, (char *)test_messages[i], message_len) == message_len, "Failed to write to buffer");
        mu_assert(RingBuffer_read(buffer, read_buffer, message_len) == message_len, "Failed to read from buffer");
        
        // Verify that read data matches written data
        mu_assert(strncmp(read_buffer, test_messages[i], message_len) == 0, "Buffer read data does not match written data");
    }
    return NULL;
}

char *test_overwrite() {
    // Test behavior when writing more data than buffer can hold
    const char *large_message = "This message is too large for the buffer";
    int write_result = RingBuffer_write(buffer, (char *)large_message, strlen(large_message));
    mu_assert(write_result == -1, "Buffer should not have enough space for large message");

    // Ensure buffer is not corrupted after attempted overwrite
    mu_assert(RingBuffer_available_data(buffer) == 0, "Buffer should be empty after failed write");
    return NULL;
}

char *test_wraparound() {
    // Test writing, reading, then writing again to ensure wraparound works
    const char *short_message = "Short";
    const char *wrap_message = "Wraparound";
    int short_len = strlen(short_message);
    int wrap_len = strlen(wrap_message);
    
    // Fill buffer to trigger wraparound
    RingBuffer_write(buffer, (char *)short_message, short_len);
    RingBuffer_read(buffer, NULL, short_len);  // Advance buffer start
    RingBuffer_write(buffer, (char *)wrap_message, wrap_len);
    
    char wrap_read[1024] = {0};
    RingBuffer_read(buffer, wrap_read, wrap_len);
    mu_assert(strcmp(wrap_read, wrap_message) == 0, "Failed to properly handle wraparound in buffer");
    return NULL;
}

char *test_destroy() {
    RingBuffer_destroy(buffer);
    mu_assert(true, "Buffer destroyed without errors.");
    return NULL;
}

char *all_tests() {
    mu_suite_start();
    
    mu_run_test(test_create);
    mu_run_test(test_write_read);
    mu_run_test(test_overwrite);
    mu_run_test(test_wraparound);
    mu_run_test(test_destroy);
    
    return NULL;
}

RUN_TESTS(all_tests);