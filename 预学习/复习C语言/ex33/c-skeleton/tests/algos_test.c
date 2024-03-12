#include "minunit.h"
#include "../src/lcthw/list_algos.h"
#include <assert.h>
#include <string.h>
#include <time.h>

//char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};
#define NUM_VALUES 5
char *values[NUM_VALUES];

List *create_words()
{
    int i = 0;
    List *words = List_create();

    for(i = 0; i < NUM_VALUES; i++) {
        values[i]=rand();
        List_push(words, values+i);
    }

    return words;
}

int is_sorted(List *words)
{
    LIST_FOREACH(words, first, next, cur) {
        if(cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}

char *test_bubble_sort()
{
    List *words = create_words();
    // should work on an already sorted list
    int rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

    List_destroy(words);

    // should work on an empty list
    words = List_create(words);
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    List_destroy(words);

    return NULL;
}

char *test_merge_sort()
{
    List *words = create_words();

    // should work on a list that needs sorting
    List *res = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    List *res2 = List_merge_sort(res, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Should still be sorted after merge sort.");
    List_destroy(res2);
    List_destroy(res);

    List_destroy(words);
    return NULL;
}


char *all_tests()
{
    mu_suite_start();
    time_t bubble_start = time(0);
    mu_run_test(test_bubble_sort);
    time_t bubble_end = time(0);
    printf("bubble sort time:%ld\n", bubble_end - bubble_start);
    
    time_t merge_start = time(0);
    mu_run_test(test_merge_sort);
    time_t merge_end = time(0);
    printf("merge sort time:%ld\n", merge_end - merge_start);
    return NULL;
}

RUN_TESTS(all_tests);

// 编译：gcc -o algos_test algos_test.c ../src/lcthw/list.c ../src/lcthw/list_algos.c
// 4096，merge大概2秒，bubble大概很久（三分钟都没跑完,感觉像是bug，但是又不是）