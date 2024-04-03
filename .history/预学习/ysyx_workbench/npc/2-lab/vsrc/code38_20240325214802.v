module code38(
    input [7:0] i_code,
    input i_en,
    output reg [2:0] o_code,
    output     [7:0] o_seg,
    output           o_en_flag
);
    integer i;
    always @(i_code or i_en) begin
        if(i_en) begin
            o_code = 3'd0;
            o_en_flag = 1'b1;
            for(i = 0; i <= 7; i = i+1)
                if(i_code[i] == 1) o_code = i[2:0];
        end
        else begin
            o_code = 3'd0;
            o_en_flag = 1'b0;
        end
    end

    seg seg_u1(
        .i_seg(o_code),
        .o_seg(o_seg)
    );
endmodule

module seg(
    input [2:0] i_seg,
    output reg [7:0] o_seg
);
    parameter num0 = 8'b11111101;
    parameter num1 = 8'b01100000;
    parameter num2 = 8'b11011010;
    parameter num3 = 8'b11110010;
    parameter num4 = 8'b01100110;
    parameter num5 = 8'b10110110;
    parameter num6 = 8'b10111110;
    parameter num7 = 8'b11100000;
    parameter num8 = 8'b11111111;
    parameter num9 = 8'b1111_0111;
    
    always @(i_seg) begin
        case(i_seg)
            3'd0 : o_seg = ~num0;
            3'd1 : o_seg = ~num1;
            3'd2 : o_seg = ~num2;
            3'd3 : o_seg = ~num3;
            3'd4 : o_seg = ~num4;
            3'd5 : o_seg = ~num5;
            3'd6 : o_seg = ~num6;
            3'd7 : o_seg = ~num7;
        endcase
    end
endmodule
