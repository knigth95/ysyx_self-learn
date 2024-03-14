#include <verilated.h>
#include"Vtop.h"

int main(int argc, char** argv, char** env) {
    if(false && argc && argv && env){}
    Vtop* top = new Vtop;
    while(!Verilated::gotFinish()) {
        top->eval();
    }
    top->final();
    delete top;
    return 0;
}