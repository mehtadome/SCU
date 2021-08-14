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
input [31:0] A;		// In1
input [31:0] B;		// In2
input [3:0] sel;	// ALUOp

// outputs
output wire [31:0] out;
output reg neg;     // output is negative
output reg zero;    // output is zero

// different selects
reg [1:0] sel_1bit;
reg [1:0] sel_2bit;

// wires
wire [31:0] mux2out;

wire [31:0] mux3out;
wire [31:0] compOut;
wire [31:0] compBout;

// read in 4-bit opcode
always@(sel)
case(sel)
    
    // Addition (B + A)
   4'b0000: begin
            end
	
	// Increment (B + 1)
	4'b0001: begin
	sel_1bit = 2'b10;
	sel_2bit = 2'b00;
	         end
	
	// Two's Compliment (0 + ~A)
	4'b0010: begin
	sel_1bit = 2'b00;
	sel_2bit = 2'b10;
	         end
	
	// Pass A (0 + A)
	4'b0100: begin
	sel_1bit = 2'b01;
	sel_2bit = 2'b00;
	         end
	         
	// Pass A (0 + A)
	4'b0111: begin
	sel_1bit = 2'b00;
	sel_2bit = 2'b00;
	         end
endcase	

twoComp tBComp(B, compBOut);
mux3to1 mux2(0, B, compBOut, sel_1bit, mux2out);
twoComp tComp(A, compOut);
mux3to1 threeOne(A, 1, compOut, sel_2bit, mux3out);
adder add32(mux2out, mux3out, out);


always@(out)
begin
    // res = 0
    if (out == 0)
        zero = 1; 
    // res < 0
    else
        zero = 0;
    neg = out[31];
end

endmodule
