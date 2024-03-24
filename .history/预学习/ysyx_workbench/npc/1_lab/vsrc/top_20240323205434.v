module MuxKey #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1) (
  output [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  MuxKeyInternal #(NR_KEY, KEY_LEN, DATA_LEN, 0) i0 (out, key, {DATA_LEN{1'b0}}, lut);
endmodulemodule mux(a,s,y);
  input  [3:0] a;
  input  [1:0] s;
  output y;
  assign y = (a[0]&~s[0]&~s[1])|(a[1]&s[0]&~s[1])|(a[2]&s[1]&~s[0])|(a[3]&s[1]&s[0]);
endmodule