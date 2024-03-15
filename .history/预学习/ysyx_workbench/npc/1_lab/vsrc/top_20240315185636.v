`include "../../../../../.history/预学习/ysyx_workbench/npc/1_lab/vsrc/top_20240315185018.v"
module // outports wire
wire   	f;

top u_top(
   .a 	( a  ),
   .b 	( b  ),
   .f 	( f  )
);
(
   input  [3:0] a,
   input  [1:0] s,
   output y
);
  assign y = (a[0]&~s[0]&~s[1])|(a[1]&s[0]&~s[1])|(a[2]&s[1]&~s[0])|(a[3]&s[1]&s[0]);
endmodule