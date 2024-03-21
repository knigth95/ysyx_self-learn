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

void nvboard_bind_all_pins(Vtop* top);

void sim_init();
void sim_exit();

void step_and_dump_wave(){
    top->eval();
    textp->timeInc(1);
    vcd->dump(textp->time());
}
void sim_init(){
    textp=new VerilatedContext;
    vcd=new VerilatedVcdC;
    top=new Vtop;
    textp->traceEverOn(true);
    //top->trace(tfp,0);
    vcd->open("dump.vcd");
}
void sim_exit(){
    step_and_dump_wave();
    vcd->close();
}
int main(int argc, char** argv){
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);//export vcd

    nvboard_bind_all_pins(&dut);
    nvboard_init();
    while(true){
        sim_init();
        top->b=0b00;  top->a=0b1110;  step_and_dump_wave();
                        top->a=0b0001;  step_and_dump_wave();
        top->b=0b01;  top->a=0b1110;  step_and_dump_wave();
                        top->a=0b0010;  step_and_dump_wave();
        top->b=0b10;  top->a=0b1010;  step_and_dump_wave();
                        top->a=0b0100;  step_and_dump_wave();
        top->b=0b11;  top->a=0b0111;  step_and_dump_wave();
                        top->a=0b1001;  step_and_dump_wave();
        sim_exit();
        dut.eval();
        nvboard_update();
    }
    nvboard_quit();

    // sim_init();
    // top->s=0b00;  top->a=0b1110;  step_and_dump_wave();
    //                 top->a=0b0001;  step_and_dump_wave();
    // top->s=0b01;  top->a=0b1110;  step_and_dump_wave();
    //                 top->a=0b0010;  step_and_dump_wave();
    // top->s=0b10;  top->a=0b1010;  step_and_dump_wave();
    //                 top->a=0b0100;  step_and_dump_wave();
    // top->s=0b11;  top->a=0b0111;  step_and_dump_wave();
    //                 top->a=0b1001;  step_and_dump_wave();
    // sim_exit();

    return 0;
}