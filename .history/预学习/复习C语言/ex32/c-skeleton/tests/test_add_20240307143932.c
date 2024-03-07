#include "minunit.h"
#include "../src/lcthw/" // 包含你的链表定义和函数声明
#include <assert.h>
#include <stdlib.h>

int tests_run = 0;

static char *test_List_create() {
    List *list = List_create();
    mu_assert("Error: List_create failed to create a list", list != NULL);
    mu_assert("Error: list->first should be NULL after creation", list->first == NULL);
    mu_assert("Error: list->last should be NULL after creation", list->last == NULL);
    List_destroy(list);
    return 0;
}

static char *test_List_push_pop() {
    List *list = List_create();
    int value1 = 1, value2 = 2;
    
    List_push(list, &value1);
    List_push(list, &value2);
    
    mu_assert("Error: list->last->value != value2", *(int *)List_pop(list) == value2);
    mu_assert("Error: list->last->value != value1 after pop", *(int *)List_pop(list) == value1);
    
    List_destroy(list);
    return 0;
}

static char *test_List_unshift_shift() {
    List *list = List_create();
    int value1 = 1, value2 = 2;
    
    List_unshift(list, &value1);
    List_unshift(list, &value2);
    
    mu_assert("Error: list->first->value != value2", *(int *)List_shift(list) == value2);
    mu_assert("Error: list->first->value != value1 after shift", *(int *)List_shift(list) == value1);
    
    List_destroy(list);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_List_create);
    mu_run_test(test_List_push_pop);
    mu_run_test(test_List_unshift_shift);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
