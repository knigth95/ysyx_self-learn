#include "verilated_vcd_c.h" //用于生成波形
#include "Vexample.h"  
#include "verilated.h"
//glibc
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// Difftest
#include <dlfcn.h>
//readline
#include <readline/readline.h>
#include <readline/history.h>
//system time
#include <sys/time.h>

//环境
Vexample* example;
int main(int argc, char** argv) {
    
    example = new Vexample{};
    int i=0;
    while(i<10){
        int a=rand()&1;
        int b=rand()&1;
        example->a=a;
        example->a=b;
        f=
        printf("a=%d,b=%d,f=%d,example->f=%d\n",a,b,f,example->f);
        example->eval();
        //assert(example->f == (a ^ b));
        i++;
    }
    return 0;
}

