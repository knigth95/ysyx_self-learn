#include "Vexample.h"
#include "verilated.h"
int main(int argc, char** argv) {
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    Vour* top = new Vour{contextp};
    while (!contextp->gotFinish()) { top->eval(); }
    deletetop;
    delete contextp;
    return 0;
}