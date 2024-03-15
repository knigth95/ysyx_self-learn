module top(
  input [3:0] a,
  input [1:0] s,
  output y
);  
  assign f=(a[0]&~b[0]&~b[1])|(a[1]&b[0]&~b[1])|(a[2]&b[1]&~b[0])|(a[3]&b[1]&b[0]);
endmodule