#include "minunit.h"
#include "../src/lcthw/dbg.h"
#include <assert.h>
#include "../src/lcthw/list.h"

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";


char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}


char *test_destroy()
{
    List_clear_destroy(list);

    return NULL;

}


char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}

char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);
    
    return NULL;
}

RUN_TESTS(all_tests);

#include "minunit.h"
#include "list.h" // 包含你的链表定义和函数声明
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
