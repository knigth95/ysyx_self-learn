#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include""

#define MAX_DATA 100
int read_string(char**out_string,int max_buffer){
    *out_string=calloc(1,max_buffer+1);
    check_mem(*out_string);
    char *result=fgetc(*out_string,max_buffer,stdin);

}