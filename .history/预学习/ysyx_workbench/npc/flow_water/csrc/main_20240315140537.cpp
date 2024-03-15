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
    while(true)
    return 0;
}