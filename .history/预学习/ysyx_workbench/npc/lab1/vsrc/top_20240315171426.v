module top(
  input [3:0]a;
  input [1:0]b;
  output f
);  
  assign f=(a[0]&b[0])
endmodule