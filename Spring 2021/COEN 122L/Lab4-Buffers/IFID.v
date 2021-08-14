`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/06/2021 01:35:06 PM
// Design Name: 
// Module Name: IFID
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


module IFID(clk, in_pc, in_instrument, out_pc, out_instrument);

//initialize inputs
input clk;
input [7:0] in_pc;
input [31:0] in_instrument;

//initialize outputs
output reg [7:0] out_pc;
output reg [31:0] out_instrument;

always@(posedge clk)
begin 
    // inputs to outputs
    out_pc = in_pc;
    out_instrument = in_instrument;
end
endmodule
