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
VerilatedVcdC* vcd;
int main(int argc, char** argv) {
    Verilated::commandArgs(argc,argv);
    example = new Vexample{};
    // 初始化波形记录器
    Verilated::traceEverOn(true); // 启用波形跟踪
    vcd = new VerilatedVcdC;
    example->trace(vcd, 5); // 设置跟踪级别
    vcd->open("./obj_dir/sim.vcd"); // 指定VCD文件位置
    int i=0;
    while(1){
        int a=rand()&1;
        int b=rand()&1;
        int f;
        example->a=a;
        example->b=b;
        example->eval();
        f=a^b;
        printf("a=%d,b=%d,f=%d,example->f=%d\n",a,b,f,example->f);
        assert(example->f == (a ^ b));
        i++;
    }
    
    return 0;
}