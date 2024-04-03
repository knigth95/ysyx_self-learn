#include <nvboard.h>
#include "Vcode38.h"

static TOP_NAME dut;

void nvboard_bind_all_pins(Vcode38* top);

VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;
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

int main() {
    nvboard_bind_all_pins(&dut);
    nvboard_init();

    while(1) {
        dut.eval();
        nvboard_update();
    }
}