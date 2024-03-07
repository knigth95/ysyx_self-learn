#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include "/home/jetson/ysyx-zzm/ysyx_self-learn/预学习/复习C语言/dbg.h"

#define MAX_DATA 100
int read_string(char**out_string,int max_buffer){
    *out_string=calloc(1,max_buffer+1);
    check_mem(*out_string);
    char *result=fgets(*out_string,max_buffer,stdin);
    check(result!=NULL,"Input error");
    return 0;
}
