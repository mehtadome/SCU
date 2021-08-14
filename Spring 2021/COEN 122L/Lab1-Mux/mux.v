`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/15/2021 05:00:57 PM
// Design Name: Ruchir Mehta
// Module Name: mux
// Project Name: Lab1
// Target Devices: 
// Tool Versions: 
// Description: Construct a 4:1 multiplexer
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module mux(A,B,C,D,select,out);
// inputs
input A,B,C,D;
input [1:0] select;
// outputs
output reg out;

// combinational logic
always@(A,B,C,D,select)

// switch case for different inputs
case(select)
    2'b00: out = A;
    2'b01: out = B;
    2'b10: out = C;
    2'b11: out = D;
endcase

endmodule
