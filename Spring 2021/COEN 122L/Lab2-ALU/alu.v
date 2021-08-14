`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Ruchir Mehta
// 
// Create Date: 04/21/2021 10:58:36 AM
// Design Name: ALU 
// Module Name: alu
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: Create an ALU that inputs INC, NEG, ADD, SUB
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module alu(A,B,sel,out,neg,zero);

// 32-bit inputs
input [31:0] A;
input [31:0] B;
input [3:0] sel;

// outputs
output [31:0] out;
output reg neg;     // output is negative
output reg zero;    // output is zero

// wires
wire [31:0] mux2out, mux3out, compOut;

// read in 4-bit opcode
always@(A,B,sel)
case(sel)
    // addition
	4'b0000: mux2to1(B, 0, sel, mux2out);
	
	// increment
	4'b0001: mux3to1(A, 1, compOut, sel, mux3out);
	
	// 2's compliment
	4'b0010: twoComp(A, mux2out);
	
	// subtraction
	4'b0011: adder(mux2out, mux3out, out);
	
endcase


always@(out)
begin
    // res = 0
    zero = 0;
    if (out == 0)
        zero = 1; // 1 for true
    
    // res < 0
    neg = 0;
    if (out[31] == 1)
        neg = 1; // 1 for true
end

endmodule
