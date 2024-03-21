module top(
   input  [3:0] a,
   input  [1:0] b,
   //output f
   output reg f
);//二位四选一选择器
  // assign f = (a[0]&~b[0]&~b[1])|(a[1]&b[0]&~b[1])|(a[2]&b[1]&~b[0])|(a[3]&b[1]&b[0]);
  always @(b or a)
    case(b)
      2'b00:f=a[0];
      2'b01:f=a[1];
      2'b10:f=a[2];
      2'b11:f=a[3];
      default: f=;
    endcase
endmodule