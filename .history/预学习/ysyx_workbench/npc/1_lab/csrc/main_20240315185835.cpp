#include "verilated_vcd_c.h"
#include "verilated.h"
#include "Vtop.h"
#include "stdio.h"
#include <nvboard.h>
#include <stdlib.h>
#include <time.h>


static TOP_NAME dut;
Vtop *top;//module object
VerilatedContext* textp=NULL;
VerilatedVcdC* vcd=NULL;

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
void step_and_dump_wave(){
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}
void sim_init(){
    contextp=new VerilatedContext;
    tfp=new VerilatedVcdC;
    top=new Vmux;
    contextp->traceEverOn(true);
    //top->trace(tfp,0);
    tfp->open("dump.vcd");
}
void sim_exit(){
    step_and_dump_wave();
    tfp->close();
}