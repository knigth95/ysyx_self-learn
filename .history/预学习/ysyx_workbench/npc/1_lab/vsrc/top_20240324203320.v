module top(
  input  [3:0] a,
  input  [1:0] s,
  output y,
);
  assign y = (a[0]&~s[0]&~s[1])|(a[1]&s[0]&~s[1])|(a[2]&s[1]&~s[0])|(a[3]&s[1]&s[0]);

  // reg [31:0] count;
  // always @(posedge clk) begin
  //   if (rst) begin led <= 1; count <= 0; end
  //   else begin
  //     if (count == 0) led <= {led[14:0], led[15]};
  //     count <= (count >= 5000000 ? 32'b0 : count + 1);
  //   end
  // end
endmodule
