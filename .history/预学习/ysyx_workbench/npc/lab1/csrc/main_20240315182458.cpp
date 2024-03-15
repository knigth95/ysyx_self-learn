#include "verilated_vcd_c.h"
#include "Vtop.h"
#include "stdio.h"
#include <nvboard.h>
#include <stdlib.h>
#include <time.h>


static TOP_NAME dut;
static Vtop *top;//module object
VerilatedContext* textp=NULL;
VerilatedVcdC* vcd=new VerilatedV;

void nvboard_bind_all_pins(TOP_NAME* top);
void step_and_dump_wave();
void sim_init();
void sim_exit();

int main(int argc, char** argv){
    //textp->commandArgs(argc, argv);
    //top=new Vtop{textp};
    nvboard_bind_all_pins(&dut);
    nvboard_init();
    sim_init();
    while(true){
        dut.eval();
        nvboard_update();
    }
    top->final();
    delete top;
    delete textp;
    nvboard_quit();
    sim_exit();
    return 0;
}

void step_and_dump_wave(){
    top->eval();
    textp->timeInc(1);
    vcd->dump(textp->time());
}
void sim_init(){
    // textp=new VerilatedContext;
    // vcd=new VerilatedVcdC;
    // top=new Vtop;
    textp->traceEverOn(true);
    //top->trace(vcd,0);
    vcd->open("dump.vcd");
}
void sim_exit(){
    step_and_dump_wave();
    vcd->close();
}