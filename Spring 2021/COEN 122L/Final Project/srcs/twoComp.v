`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/22/2021 12:36:02 PM
// Design Name: 
// Module Name: twoComp
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


module twoComp(A,out);

input [31:0] A;
output reg [31:0] out;

always@ (A)
begin    
    out = (~A) + 1;
    end
endmodule
