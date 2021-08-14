`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/27/2021 12:16:29 PM
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


module IFID(clk, in_pc, in_instruction, out_pc, out_instruction);

    //initialize inputs
    input clk;
    input [31:0] in_pc;
    input [31:0] in_instruction;

    //initialize outputs
    output reg [31:0] out_pc;
    output reg [31:0] out_instruction;

    always@(posedge clk)
    begin 
        // inputs to outputs
        out_pc = in_pc;
        out_instruction = in_instruction;
    end
endmodule

