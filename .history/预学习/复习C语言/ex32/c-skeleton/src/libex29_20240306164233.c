#include<stdio.h>
#include<ctype.h>
#include<dlfcn.h>
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
    char *lib_file=argv[1];
    char *func_to_run=argv[2];
    char *data=argv[3];

    void *lib=dlopen(lib_file,func_to_run);
    check(lib!=NULL,"Failed to open the library %s: %s",lib_file,dlerror());

    lib_function func=dlsym(lib,func_to_run);
    check(func!=NULL,"Did not find %s function in the library %s: %s",func_to_run,lib_file,dlerror());

    rc=func(data);
    check(rc==0,"Function %s return %d for data: %s",func_to_run,rc,data);

    rc=dlclose(lib);
    check(rc==0,"Failed to close %s",lib_file);
    return 0;

error:
    return 1;
}