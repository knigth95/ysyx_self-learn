#include "verilated_vcd_c.h"
#include "Vtop.h"
#include "stdio.h"
#include <nvboard.h>
#include <stdlib.h>
#include <time.h>



void nvboard_bind_all_pins(Vtop* top);



int main(int argc, char** argv){
    static TOP_NAME dut;
Vtop *top;//module object
    VerilatedContext* textp=new VerilatedContext;
    textp->commandArgs(argc, argv);
    
    return 0;
}