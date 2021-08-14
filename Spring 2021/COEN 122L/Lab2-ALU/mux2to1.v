module mux2to1(A, B, sel, out);
input [31:0] A;
input [31:0] B;
input sel;
output reg [31:0] out;

always@(A, B, sel)
case(sel)
    2'b0: out = A;
    2'b1: out = B;
endcase

endmodule