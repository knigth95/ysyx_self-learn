#include "verilated_vcd_c.h" //用于生成波形
#include "Vexample.h"  
#include "verilated.h"
//dpi-c
#include "Vtop__Dpi.h"
#include <verilated_dpi.h>
//glibc
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// Difftest
#include <dlfcn.h>
//readline
#include <readline/readline.h>
#include <readline/history.h>
//system time
#include <sys/time.h>

//环境
VerilatedContext* contextp;
Vexample* example;
VerilatedVcdC* tfp;

vluint64_t main_time = 0;//仿真时间
double sc_time_stamp() { return main_time; }
uint64_t ref_regs[33];
void hit_exit(int status)