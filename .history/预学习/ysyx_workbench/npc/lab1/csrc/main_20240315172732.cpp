#include "verilated_vcd_c.h"
#include "Vtop.h"
#include "stdio.h"
#include <nvboard.h>
#include <stdlib.h>
#include <time.h>


static TOP_NAME dut;
Vtop *top;//module object
void nvboard_bind_all_pins(TOP_NAME* top);

VerilatedContext* contextp=NULL;
VerilatedVcdC* tfp=NULL;//for gen wave
static TOP_NAME dut;
static Vmux* top;

void sim_init();
void sim_exit
void nvboard_bind_all_pins(Vmux* top);

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

int main(){
    nvboard_bind_all_pins(&dut);
    nvboard_init();

    //sim_init();
    while(true){
        dut.eval();
        nvboard_update();
    }
    nvboard_quit();
    //sim_exit();
}

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
