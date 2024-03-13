#include "../src/lcthw/ringbuffer_posix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minunit.h"

void fuzz_test(RingBuffer *rb) {
    srand(time(NULL));
    char data[256];
    char read_data[256];
    for (int i = 0; i < 10000; i++) {
        int len = rand() % 255 + 1;  // Generate a random length for the data
        for (int j = 0; j < len; j++) {
            data[j] = rand() % 256;  // Generate random data
        }
        RingBuffer_write(rb, data, len);
        RingBuffer_read(rb, read_data, len);

        // Optionally compare data and read_data for correctness
    }
}

int main() {
    RingBuffer *rb = RingBuffer_create(1024);  // Create a smaller buffer for testing
    fuzz_test(rb);
    RingBuffer_destroy(rb);
    //mu_run_test(fuzz_test);
    printf("Fuzz test completed.\n");
    return 0;
}

//编译gcc -o ringbuffer_fuzz_test ../src/lcthw/ringbuffer_posix.c  ringbuffer_fuzz_test.c