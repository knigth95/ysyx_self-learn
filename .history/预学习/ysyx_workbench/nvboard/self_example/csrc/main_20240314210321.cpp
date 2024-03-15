#include <nvboard.h>
#include <Vtop.h>

static TOP_NAME top;

void nvboard_bind_all_pins(Vtop* top);

static void single_cycle() {
  top.clk = 0; top.eval();
  top.clk = 1; top.eval();
}

static void reset(int n) {
  top.rst = 1;
  while (n -- > 0) single_cycle();
  top.rst = 0;
}

void step_and_dump_wave()
{
    top->eval();input clk,
    // input rst,
    // input [4:0] btn,
    // input [7:0] sw,
    // input ps2_clk,
    // input ps2_data,
    // input uart_rx,

    // output uart_tx,
    // output [15:0] ledr,
    // output VGA_CLK,
    // output VGA_HSYNC,
    // output VGA_VSYNC,
    // output VGA_BLANK_N,
    // output [7:0] VGA_R,
    // output [7:0] VGA_G,
    // output [7:0] VGA_B,
    // output [7:0] seg0,
    // output [7:0] seg1,
    // output [7:0] seg2,
    // output [7:0] seg3,
    // output [7:0] seg4,
    // output [7:0] seg5,
    // output [7:0] seg6,
    // output [7:0] seg7,
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}

void sim_init()
{
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    top = new Vtop;
    contextp->traceEverOn(true);
    top->trace(tfp, 3);
    tfp->open("./wave.vcd");
}

void sim_exit()
{
    step_and_dump_wave();
    tfp->close();
}

int main() {
  nvboard_bind_all_pins(&top);
  nvboard_init();

  reset(10);

  while(1) {
    nvboard_update();
    single_cycle();
  }
}