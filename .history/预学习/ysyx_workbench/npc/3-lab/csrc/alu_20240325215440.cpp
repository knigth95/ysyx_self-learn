#include "verilated.h"
#include "Valu.h"
#include "nvboard.h"
#include <stdlib.h>

static TOP_NAME dut;

void nvboard_bind_all_pins(Vcode38* top);

// VerilatedContext* contextp = NULL;
// VerilatedVcdC* tfp = NULL;
// void step_and_dump_wave() {
//     top->eval();
//     contextp->timeInc(1);
//     tfp->dump(contextp->time());
// }

// void sim_init() {
//     contextp = new VerilatedContext;
//     tfp = new VerilatedVcdC;
//     top = new Vmux241;
//     contextp->traceEverOn(true);
//     top->trace(tfp,10);
//     tfp->open("mux241.vcd");
// }

// void sim_exit() {
//     step_and_dump_wave();
//     tfp->close();
// }



VerilatedContext* contextp=NULL;
static TOP_NAME dut;
static Valu* top;
void nvboard_bind_all_pins(Valu* top);
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