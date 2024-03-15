#include "verilated_vcd_c.h"
#include "Vtop.h"
#include "stdio.h"
#include <nvboard.h>
#include <stdlib.h>
#include <time.h>


static TOP_NAME dut;
Vtop *top;//module object


int main(int argc, char** argv){
    
    VerilatedContext* textp=NULL;
    VerilatedVcdC* vcd
    textp->commandArgs(argc, argv);
    top=new Vtop{textp};
    nvboard_bind_all_pins(&dut);
    nvboard_init();
    reset(num);
    while(true){
        nvboard_update();
        single_cycle();
    }
    top->final();
    delete top;
    delete textp;
    nvboard_quit();
    return 0;
}
