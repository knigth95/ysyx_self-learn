#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>


struct Person {
    char name[26];
    int age;
    int height;
    int weight;
};

// struct Person *Person_create(char *name, int age, int height, int weight)
// {
//     struct Person *who = malloc(sizeof(struct Person));
//     assert(who != NULL);

//     who->name = strdup(name);
//     who->age = age;
//     who->height = height;
//     who->weight = weight;

//     return who;
// }

// void Person_destroy(struct Person *who)
// {
//     assert(who != NULL);
//     free(who->name);
//     free(who);
// }

void Person_print(struct Person who)
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    struct Person joe = {"Joe Alex", 32, 64, 140};
    struct Person frank = {"Frank Blank", 20, 72, 180};

    // make everyone age 20 years and print them again
    strcpy(joe.name, "Joe Smith");
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);

    Person_print(joe);
    Person_print(frank);

    return 0;
}