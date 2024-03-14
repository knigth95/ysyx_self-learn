module example(
   input a,
   input b,
   output f
);
   assign f=a^b;
endmodule
//最后一行有空行就不会报错（这是什么语法！！）
