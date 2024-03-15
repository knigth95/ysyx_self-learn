#include "verilated_vcd_c.h"
#include "Vtop.h"
#include "stdio.h"
#include <nvboard.h>
#include <stdlib.h>
#include <time.h>



void nvboard_bind_all_pins(Vtop* top);
void reset(int num,static TOP_NAME dut);
void single_cycle(static TOP_NAME dut);

int main(int argc, char** argv){
    int num=10;
    static TOP_NAME dut;
    Vtop *top;//module object
    VerilatedContext* textp=new VerilatedContext;
    textp->commandArgs(argc, argv);
    top=new Vtop{textp};
    nvboard_bind_all_pins(&dut);
    nvboard_init();
    reset(num,dut);
    while(true){
        nvboard_update();
        single_cycle(dut);
    }
    top->final();
    delete top;
    delete textp;
    nvboard_quit();
    return 0;
}

void single_cycle(static TOP_NAME dut){
    dut.clk=0;
    dut.eval();
    dut.clk=1;
    dut.eval();
}

void reset(int num,static TOP_NAME dut){
    dut.rst=1;
    while(num-->0) single_cycle(dut);
    dut.rst=0;
}