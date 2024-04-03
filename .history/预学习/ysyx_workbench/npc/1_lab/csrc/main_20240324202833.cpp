#include <nvboard.h>
//#include"../nvboard/include/nvboard.h"
#include <Vtop.h>
#include <verilated.h>
#include "verilated_vcd_c.h"

VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;

static Vtop* top;

static Vtop dut;

void nvboard_bind_all_pins(Vtop* top);

void step_and_dump_wave() {
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}

static void single_cycle() {
  dut.clk = 0; dut.eval();
  dut.clk = 1; dut.eval();
}

static void reset(int n) {
  dut.rst = 1;
  while (n -- > 0) single_cycle();
  dut.rst = 0;
}

void sim_init() {
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    top = new Vtop;
    contextp->traceEverOn(true);
    top->trace(tfp,10);
    tfp->open("mux241.vcd");
}

void sim_exit() {
    step_and_dump_wave();
    tfp->close();
}

int main() {
  nvboard_bind_all_pins(&dut);
  nvboard_init();
  sim_init();
  reset(1);
  int i=0;
  top->a[0]=0b00;
  top->a[1]=0b01;
  top->a[2]=0b10;
  top->a[3]=0b11;
  while(1) {
    nvboard_update();
    while(i<50){
      i++;
      top->s=
    }
    single_cycle();
  }

  nvboard_quit();
}



// #include "verilated_vcd_c.h"
// #include "Vtop.h"
// #include "stdio.h"
// #include <nvboard.h>
// #include <stdlib.h>
// #include <time.h>


// static TOP_NAME dut;
// Vtop *top;//module object
// VerilatedContext* textp=NULL;
// VerilatedVcdC* vcd=NULL;

// void nvboard_bind_all_pins(Vtop* top);

// // void single_cycle(){
// //     dut.clk=0;
// //     dut.eval();
// //     dut.clk=1;
// //     dut.eval();
// // }

// int main(int argc, char** argv){
//     Verilated::commandArgs(argc, argv);
//     Verilated::traceEverOn(true);//export vcd

//     nvboard_bind_all_pins(&dut);
//     nvboard_init();
//     //textp->traceEverOn(true);
//     //top->trace(vcd,0);
//     //vcd->open("dump.vcd");
//     while(true){
//         dut.eval();
//         nvboard_update();

//     }
//     nvboard_quit();

//     // sim_init();
//     // top->s=0b00;  top->a=0b1110;  step_and_dump_wave();
//     //                 top->a=0b0001;  step_and_dump_wave();
//     // top->s=0b01;  top->a=0b1110;  step_and_dump_wave();
//     //                 top->a=0b0010;  step_and_dump_wave();
//     // top->s=0b10;  top->a=0b1010;  step_and_dump_wave();
//     //                 top->a=0b0100;  step_and_dump_wave();
//     // top->s=0b11;  top->a=0b0111;  step_and_dump_wave();
//     //                 top->a=0b1001;  step_and_dump_wave();
//     // sim_exit();

//     return 0;
// }