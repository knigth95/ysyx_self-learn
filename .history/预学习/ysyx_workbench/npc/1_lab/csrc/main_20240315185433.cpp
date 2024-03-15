#include "verilated_vcd_c.h"
#include "Vtop.h"
#include "stdio.h"
#include <nvboard.h>
#include <stdlib.h>
#include <time.h>

static TOP_NAME dut;
Vtop *top;//module object

void nvboard_bind_all_pins(Vtop* top);

int main(int argc, char** argv){
    // Verilated::commandArgs(argc, argv);
    // Verilated::traceEverOn(true);//export vcd

    nvboard_bind_all_pins(&dut);
    nvboard_init();
    while(true){
        dut.eval();
        nvboard_update();
    }
    nvboard_quit();
    return 0;
}