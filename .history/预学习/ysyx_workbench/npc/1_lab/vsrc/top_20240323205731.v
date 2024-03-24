module top(
  input  [3:0] a,
  input  [1:0] s,
  output y
);
  assign y = (a[0]&~s[0]&~s[1])|(a[1]&s[0]&~s[1])|(a[2]&s[1]&~s[0])|(a[3]&s[1]&s[0]);

endmodule

module mutex41 (
    input clk,
    input rst,
    input [9:0] sw,
    output [15:0] ledr
);

    MuxKeyWithDefault #(4, 2, 2) i0 (ledr[1:0], sw[1:0], 2'b0, {
    2'b00, sw[3:2],
    2'b01, sw[5:4],
    2'b10, sw[7:6],
    2'b11, sw[9:8]
  });

endmodule