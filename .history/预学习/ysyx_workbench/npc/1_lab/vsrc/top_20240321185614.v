module top(
   input  [3:0] a,
   input  [1:0] b,
   output f
);//二位四选一选择器
  // assign f = (a[0]&~b[0]&~b[1])|(a[1]&b[0]&~b[1])|(a[2]&b[1]&~b[0])|(a[3]&b[1]&b[0]);
  always @(s or a)
    case(s)
      2'b00:

endmodule