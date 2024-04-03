#include <nvboard.h>
//#include"../nvboard/include/nvboard.h"
#include <Vtop.h>
#include <verilated.h>
#include "verilated_vcd_c.h"

TOPNAME = mux241
NXDC_FILE = constr/mux241.nxdc
INC_PATH ?= 
GTKWAVE = gtkwave

VERILATOR = verilator
VERILATOR_CFLAGS += --MMD --build --cc \
					-O3 --x-assign fast --x-initial fast --noassert \

VERILATOR_ARGUMENTS += --cc --build
VERILATOR_ARGUMENTS += --Wall 
VERILATOR_ARGUMENTS += --exe
VERILATOR_ARGUMENTS += --trace
VERILATOR_TOP += --top-module mux241

VERILATOR_INPUT += vsrc/*.v
VERILATOR_INPUT += csrc/*.cpp

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

default: $(BIN)

$(shell mkdir -p $(BUILD_DIR))

SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILE)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
CSRCS += $(SRC_AUTO_BIND)

include $(NVBOARD_HOME)/scripts/nvboard.mk

INCFLAGS = $(addprefix -I , $(INC_PATH))
CFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""
LDFLAGS += -lSDL2 -lSDL2_image

$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

all: default

nvb: $(BIN)
	@$^

ver:
	@echo
	@echo "----------Switch Exercise----------"
	@echo
	@echo "----------Verilator Compile--------"
	$(VERILATOR) $(VERILATOR_TOP) $(VERILATOR_ARGUMENTS) $(VERILATOR_INPUT)
	@echo
	@echo "----------Generating Wavefrom------"
	@rm -rf logs
	obj_dir/V$(TOPNAME) +trace
	@echo
	@echo "----------Done---------------------"
	@echo "You can make GTKwave to see the wavefroms." 

wave:
	@echo "Opening dump.vcd"
	$(GTKWAVE) $(TOPNAME).vcd

test:
	@echo "TOPNAME: $(TOPNAME)"
	@echo "VERILATOR_CC: $(VERILATOR_CC)"
	@echo "VERILATOR_BUILD: $(VERILATOR_BUILD)"
	@echo "VERILATOR_CFLAGS: $(VERILATOR_CFLAGS)"
clean:
	rm -rf $(BUILD_DIR) obj_dir

.PHONY: default all clean run

// VerilatedContext* contextp = NULL;
// VerilatedVcdC* tfp = NULL;

// static Vtop* top;
// static TOP_NAME dut;
// //static Vtop dut;

// void nvboard_bind_all_pins(Vtop* top);

// void step_and_dump_wave() {
//     top->eval();
//     contextp->timeInc(1);
//     tfp->dump(contextp->time());
// }

// static void single_cycle() {
//   top.clk = 0; top.eval();
//   top.clk = 1; top.eval();
// }

// static void reset(int n) {
//   top.rst = 1;
//   while (n -- > 0) single_cycle();
//   top.rst = 0;
// }

// void sim_init() {
//     contextp = new VerilatedContext;
//     tfp = new VerilatedVcdC;
//     top = new Vtop;
//     contextp->traceEverOn(true);
//     top->trace(tfp,10);
//     tfp->open("mux241.vcd");
// }

// void sim_exit() {
//     step_and_dump_wave();
//     tfp->close();
// }



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