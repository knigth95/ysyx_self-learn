#include "verilated_vcd_c.h"
#include "Vtop.h"
#include "stdio.h"
#include <nvboard.h>
#include <stdlib.h>
#include <time.h>


static TOP_NAME dut;
Vtop *top;//module object
void nvboard_bind_all_pins(Vmux* top);

int main(int argc, char** argv){
    VerilatedContext* textp=NULL;
    VerilatedVcdC* vcd=NULL;
    //textp->commandArgs(argc, argv);
    //top=new Vtop{textp};
    nvboard_bind_all_pins(&dut);
    nvboard_init();

    while(true){
        dut.eval();
        nvboard_update();
    }
    top->final();
    delete top;
    delete textp;
    nvboard_quit();
    return 0;
}
