module top(
   input  [3:0] a,
   input  [1:0] b,
   output f
);//二位四选一选择器
  // assign f = (a[0]&~b[0]&~b[1])|(a[1]&b[0]&~b[1])|(a[2]&b[1]&~b[0])|(a[3]&b[1]&b[0]);
  always @(s or a)
    case(s)
      2'b00:y=a[0];
      2'b01:y=a[1];
      2'b10:y=a[2];
      2'b11:y=a[3];
      default:y=2'b00;
    endcase
endmodule