#include "Vexample.h"
#include "verilated.h"
int main(int argc, char** argv,char** env) {
    if(false && argc && argv && env){}
    Vexample* top=new Vexample;
    while(!Verilated::gotFinish()){
        top->eval();
    }
    top->final();
    delete top;
    return 0;
}