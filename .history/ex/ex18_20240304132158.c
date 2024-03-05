#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>

/** Error handler. */
void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

// Function pointer typedefs
typedef int (*compare_cb)(int a, int b);
typedef void (*sort_function)(int *numbers, int count, compare_cb cmp);

/** Merge function for merge sort. */
void merge(int *numbers, int *helper, int low, int middle, int high, compare_cb cmp)
{
    for (int i = low; i <= high; i++) {
        helper[i] = numbers[i];
    }

    int helperLeft = low;
    int helperRight = middle + 1;
    int current = low;

    while (helperLeft <= middle && helperRight <= high) {
        if (cmp(helper[helperLeft], helper[helperRight]) <= 0) {
            numbers[current++] = helper[helperLeft++];
        } else {
            numbers[current++] = helper[helperRight++];
        }
    }

    for (int i = 0; i <= middle - helperLeft; i++) {
        numbers[current + i] = helper[helperLeft + i];
    }
}

/** Recursive function for merge sort. */
void merge_sort_rec(int *numbers, int *helper, int low, int high, compare_cb cmp)
{
    if (low < high) {
        int middle = (low + high) / 2;
        merge_sort_rec(numbers, helper, low, middle, cmp);
        merge_sort_rec(numbers, helper, middle + 1, high, cmp);
        merge(numbers, helper, low, middle, high, cmp);
    }
}

/** Wrapper function for merge sort. */
void merge_sort(int *numbers, int count, compare_cb cmp)
{
    int *helper = malloc(count * sizeof(int));
    if (!helper) die("Memory error.");

    merge_sort_rec(numbers, helper, 0, count - 1, cmp);
    free(helper);
}

/** Bubble sort function. */
void bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (cmp(numbers[j], numbers[j + 1]) > 0) {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}

/** Comparison functions. */
int sorted_order(int a, int b) { return a - b; }
int reverse_order(int a, int b) { return b - a; }
int strange_order(int a, int b) { return (a == 0 || b == 0) ? 0 : a % b; }

/** Test sorting correctness and performance. */
void test_sorting(int *original, int count, sort_function sort, compare_cb cmp, const char *algorithm_name)
{
    int *numbers = malloc(count * sizeof(int));
    memcpy(numbers, original, count * sizeof(int));  // Copy the original array to avoid modifying it

    clock_t start = clock();
    sort(numbers, count, cmp);
    clock_t end = clock();

    printf("%s sorted: ", algorithm_name);
    for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    printf("%s took %f seconds.\n", algorithm_name, (double)(end - start) / CLOCKS_PER_SEC);

    free(numbers);
}

/** Main function. */
int main(int argc, char *argv[])
{
    if (argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int *numbers = malloc(count * sizeof(int));
    if (!numbers) die("Memory error.");

    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    test_sorting(numbers, count, bubble_sort, sorted_order, "Bubble Sort");
    test_sorting(numbers, count, merge_sort, sorted_order, "Merge Sort");

    free(numbers);
    return 0;
}
