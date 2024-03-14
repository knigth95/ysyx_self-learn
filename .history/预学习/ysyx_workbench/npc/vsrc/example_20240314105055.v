module example(
   input a,
   input b,
   output f
);
   assign f=a^b;
endmodule
//有空行就不会报错（）