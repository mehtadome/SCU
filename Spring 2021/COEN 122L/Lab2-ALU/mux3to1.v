// select = sel

module mux3to1(A, B, cin, sel, out);
input [31:0] A;
input [31:0] B;
input [31:0] cin;
input [1:0] sel;
output reg [31:0] out;

always@(A, B, cin, sel)
case(sel)
    2'b00: out = A;
    2'b01: out = B;
    2'b10: out = cinn;
endcase

endmodule