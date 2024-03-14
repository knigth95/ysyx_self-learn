#include "verilated_vcd_c.h" //用于生成波形
#include "Vexample.h"  
#include "verilated.h"
//dpi-c
#include "Vtop__Dpi.h"
#include <verilated_dpi.h>
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
int main(int argc, char** argv, char** env) {
    
    example = new Vexample{contextp};
    while(1){
        int a=rand()&1;
        int b=rand()&1;
        example->a=a;
        example->a=b;
        example->eval();
        printf("a=%d,b=%d,f=%d\n",a,b,example->f);
        assert(example->f == (a^b))
    }
    return 0;
}

