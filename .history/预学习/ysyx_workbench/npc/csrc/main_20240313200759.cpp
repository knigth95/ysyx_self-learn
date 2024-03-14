#include <verilated.h>// verilator官方库
#include "Vtop.h"//top.v会被封装为头文件供c++调用
 
int main(int argc, char** argv, char** env) {
    if (false && argc && argv && env) {}    
    Vtop* top = new Vtop;// 构建verilator模型，可以通过类型调用top中的参数
    while (!Verilated::gotFinish()) {// 开始仿真直到$finish 
        top->eval();// Evaluate model
    }
    top->final();//结束仿真    
    delete top;// 清除模型   
    return 0;// Return good completion status
}