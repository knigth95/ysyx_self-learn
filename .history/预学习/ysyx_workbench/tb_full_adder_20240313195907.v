`timescale 1ps/1ps                 // 1.设置timescale，时间单位可设为1ps，精度1ps
`include "full_adder.v"            //   有时候编译提示需要include头文件
                                   //   `include相当于C里的#include
 
module tb_full_adder;              // 2.写出与testbench重名的module
 
    reg Ai, Bi, Ci;                // 3.列出例化所用到的变量
    wire Si, Ciout;
 
    full_adder name(               // 4.例化full_adder.v里的全加器模块
        .Ai(Ai),
        .Bi(Bi),
        .Ci(Ci),
        .Si(Si),
        .Ciout(Ciout));
 
    initial begin                  // 5.下面开始编写测试数据：
 
        $dumpfile("wave.vcd");     //   产生波形文件的命令
        $dumpvars;                 //   使所有变量都参与仿真的命令
 
        Ai=1'b0; Bi=1'b0; Ci=1'b0; // 6.以一个时间单位(#1)，本例中即1ps的间隔输入测试数据
        #1  Ai=1'b0; Bi=1'b0; Ci=1'b1;
        #1  Ai=1'b0; Bi=1'b1; Ci=1'b0;
        #1  Ai=1'b0; Bi=1'b1; Ci=1'b1;
        #1  Ai=1'b1; Bi=1'b0; Ci=1'b0;
        #1  Ai=1'b1; Bi=1'b0; Ci=1'b1;
        #1  Ai=1'b1; Bi=1'b1; Ci=1'b0;
        #1  Ai=1'b1; Bi=1'b1; Ci=1'b1;
        #1;
    end
endmodule