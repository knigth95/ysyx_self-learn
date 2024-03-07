#include<stdio.h>
#include<ctype.h>
#include"dbg.h"

int print_a_message(const char* msg){
    printf("A STring:%s\n",msg);
    return 0;
}

int uppercase(const char *msg){
    int i=0;
    for(i=0;msg[i]!='\0';i++){
        printf("%c",toupper(msg[i]));
    }
    printf("\n");
    return 0;
}

int lowercase(const char *msg){
    int i=0;
    for(i=0;msg[i]!='\0';i++){
        printf("%c",tolower(msg[i]));
    }
    printf("\n");
    return 0;
}
int fail_on_purpose(const char *msg){
    return 1;
}
typedef int (*lib_function)(const char *data);

int main(int argc,char *argv[]){
    int rc=0;
    check(argc==4,"USAGE: ex29 libex29.so function data");
    
}