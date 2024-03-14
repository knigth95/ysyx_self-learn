module full_adder(Ai,Bi,Ci,Si,Ciout);
    input        Ai;           //输入端口
    input        Bi;           //输入端口
    input        Ci;           //低位进位,输入端口
    output     Si;             //本位和，输出端口
    output   Ciout;            //向高位进位，输出端口
    assign   Si = Ci^Ai^Bi;
    assign   Ciout = Ai & Bi|(Ai^Bi) & Ci;
endmodule