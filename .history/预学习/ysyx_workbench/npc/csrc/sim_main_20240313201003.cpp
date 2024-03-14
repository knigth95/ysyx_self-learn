#include <verilated.h>
#include"Vtop.h"

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Vtop* top = new Vtop;
    while (!Verilated::gotFinish()) {
        top->eval();
    }
    delete top;
    return 0;
}