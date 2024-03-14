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
// Vexample* top=new Vexample{code};
// VerilatedVcdC* vcd=new VerilatedVcdC();

int main(int argc, char** argv) {
    VerilatedContext textp=new VerilatedContext;
    textp->commandArgs(argc, argv);
    while(!textp->gotFinish()){
        int a=rand()&1
    }
    vcd->close();
    delete top;
    delete vcd;
    return 0;
    // Verilated::commandArgs(argc,argv);
    // //example = new Vexample{};
    // // 初始化波形记录器
    // Verilated::traceEverOn(true); // 启用波形跟踪
    // //VerilatedVcdC *vcd = new VerilatedVcdC();
    // //Vexanple *example=new Vexample("example");
    // top->trace(vcd, 0); // 设置跟踪级别
    // vcd->open("./obj_dir/sim.vcd"); // 指定VCD文件位置
    // int i=0;
    // while(i<100 && !code->gotFinish()) {
    //     int a=rand()&1;
    //     int b=rand()&1;
    //     int f;
    //     top->a=a;
    //     top->b=b;
    //     top->eval();
    //     f=a^b;
    //     printf("a=%d,b=%d,f=%d,example->f=%d\n",a,b,f,top->f);
    //     top->dump(i);
    //     assert(top->f == (a ^ b));
    //     i++;
    // }
    
}