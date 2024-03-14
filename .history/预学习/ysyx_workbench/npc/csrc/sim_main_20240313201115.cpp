#include <verilated.h>
#include"Vtop.h"

int main(int argc, char** argv, char** env) {
    if(false && argc && argv && env){}
    Vtop* top = new Vtop;
    while(!Verilated::gotFinish()) {
        top->eval();
    }
    top->final();//结束仿真
    delete top;//清除
    return 0;
}