`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/06/2021 01:36:05 PM
// Design Name: 
// Module Name: EXMEMWB
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


module EXMEMWB(clk, Neg, Zero, reg_wrt, mem_to_reg, pc_to_reg, branch_neg, branch_Zero, jump, jump_mem, ALU, data_mem, rd, 
adder, Neg_out, Zero_out, reg_wrt_out, mem_to_reg_out, pc_to_reg_out, branch_neg_out, branch_Zero_out, jump_out, jump_mem_out, 
ALU_out, data_mem_out, rd_out, adder_out);

// nputs
input clk;
input Neg;
input Zero;
input reg_wrt;
input mem_to_reg;
input pc_to_reg;
input branch_neg;
input branch_Zero;
input jump;
input jump_mem;

// rs+rt
input [31:0] ALU; 
// more inputs
input [31:0] data_mem;
input [5:0] rd;
input [31:0] adder;

// outputs
output reg Neg_out;
output reg Zero_out;
output reg reg_wrt_out;
output reg mem_to_reg_out;
output reg pc_to_reg_out;
output reg branch_neg_out;
output reg branch_Zero_out;
output reg jump_out;
output reg jump_mem_out;

output reg [31:0] ALU_out;
output reg [31:0] data_mem_out;
output reg [5:0] rd_out;
output reg [31:0] adder_out;

always@ (posedge clk)
begin 
    // inputs to outputs
    Neg_out = Neg;
    Zero_out = Zero;
    reg_wrt_out = reg_wrt;
    mem_to_reg_out = mem_to_reg;
    pc_to_reg_out = pc_to_reg;
    branch_neg_out = branch_neg;
    branch_Zero_out = branch_Zero;
    jump_out = jump;
    jump_mem_out = jump_mem;

    ALU_out = ALU;
    data_mem_out = data_mem;
    rd_out = rd;
    adder_out = adder;   
end
endmodule
