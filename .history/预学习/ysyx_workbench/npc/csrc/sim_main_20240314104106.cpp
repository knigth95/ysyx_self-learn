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

int main(int argc, char** argv, char** env) {
    contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    example = new Vexample{contextp};
    //VCD波形设置 start
    Verilated::traceEverOn(true);
    tfp = new VerilatedVcdC;
    example->trace(tfp, 0);
    tfp->open("waveform.vcd");
    pmem_init();
    cpu_init();

    #ifdef CONFIG_DIFFTEST
        init_difftest();
    #endif
    sdb_mainloop();
    return 0;
}

