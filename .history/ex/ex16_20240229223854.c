#include <stdio.h>
#include <string.h>

struct Person {
    char name[50];  // 使用字符数组代替字符指针
    int age;
    int height;
    int weight;
};

// 初始化结构体的函数现在不需要返回指针
void Person_create(struct Person *who, char *name, int age, int height, int weight)
{
    strcpy(who->name, name);  // 使用strcpy复制字符串
    who->age = age;
    who->height = height;
    who->weight = weight;
}

// 由于不再动态分配内存，所以不需要销毁函数

void Person_print(struct Person who)  // 直接传递结构体而不是指针
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
    struct Person joe, frank;  // 直接在栈上创建结构体变量

    // 初始化结构体变量
    Person_create(&joe, "Joe Alex", 32, 64, 140);
    Person_create(&frank, "Frank Blank", 20, 72, 180);

    // 打印结构体信息
    printf("Joe is at memory location %p:\n", (void*)&joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", (void*)&frank);
    Person_print(frank);

    // 修改结构体成员并重新打印
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);

    // 不需要调用销毁函数，因为没有动态分配内存

    return 0;
}
