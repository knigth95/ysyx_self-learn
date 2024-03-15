module top(
  input [3:0]a;
  input [1:0]b;
  output f
);  
  assign f=(a[0]&~b[0]&~b[1])|(a[1]&s[0]&~s[1])|(a[2]&s[1]&~s[0])|(a[3]&s[1]&s[0]);
endmodule