#include "Vexample.h"
#include "verilated.h"
int main(int argc, char** argv) {
    if(false && argc && argv && env){}
    Vexample* top=new Vexample;
    while(!Verilated::gotFinish()){
        top->eval();
    }
    
    delete top;
    return 0;
}