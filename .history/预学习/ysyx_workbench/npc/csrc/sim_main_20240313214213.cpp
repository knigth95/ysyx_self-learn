#include "Vexample.h"
#include "verilated.h"
int main(int argc, char** argv,char** env) {
    if(false && argc && argv && env){}
    Vexample* example=new Vexample;
    while(!Verilated::gotFinish()){
        example->eval();
    }
    example->final();
    delete top;
    return 0;
}