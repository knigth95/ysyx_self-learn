#include "verilated_vcd_c.h"
#include "Vtop.h"
#include "stdio.h"
#include <nvboard.h>
#include <stdlib.h>
#include <time.h>


static TOP_NAME dut;
Vtop *top;//module object
VerilatedContext* textp=NULL;
VerilatedVcdC* vcd=NULL;

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
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}
void sim_init(){
    contextp=new VerilatedContext;
    tfp=new VerilatedVcdC;
    top=new Vtop;
    contextp->traceEverOn(true);
    //top->trace(tfp,0);
    tfp->open("dump.vcd");
}
void sim_exit(){
    step_and_dump_wave();
    tfp->close();
}