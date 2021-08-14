`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/22/2021 12:34:56 PM
// Design Name: 
// Module Name: 3to1mux
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


// select = sel

module mux3to1(A, B, C, sel, out);
input [31:0] A;
input [31:0] B;
input [31:0] C;

input [1:0] sel;
output reg [31:0] out;

always@(A, B, C, sel)
case(sel)
    // 0
    2'b00: out = A;
    // 1
    2'b01: out = B;
    // 2
    2'b10: out = C;
endcase

endmodule