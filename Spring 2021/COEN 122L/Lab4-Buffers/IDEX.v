`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/06/2021 01:35:33 PM
// Design Name: 
// Module Name: IDEX
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


module IDEX(clk, reg_wrt, mem_to_reg, pc_to_reg, branch_neg, branch_Zero, ALU_op, mem_rd, mem_wrt, jump, jump_mem, rs, rt,rd, 
adder, reg_wrt_out, mem_to_reg_out, pc_to_reg_out, branch_neg_out, branch_Zero_out, ALU_op_out, mem_rd_out, mem_wrt_out,
jump_out, jump_mem_out, rs_out, rt_out, rd_out, adder_out);

// inputs
input clk;
input reg_wrt;
input mem_to_reg;
input pc_to_reg;
input branch_neg;
input branch_Zero;
input jump;
input jump_mem;
input mem_rd;
input mem_wrt;

input [3:0] ALU_op;
input [31:0] rs;
input [31:0] rt;
input [5:0] rd;

input [31:0] adder;

// outputs
output reg reg_wrt_out;
output reg mem_to_reg_out;
output reg pc_to_reg_out;
output reg branch_neg_out;
output reg branch_Zero_out;
output reg jump_out;
output reg jump_mem_out;
output reg mem_rd_out;
output reg mem_wrt_out;

output reg [3:0] ALU_op_out;
output reg [31:0] rs_out;
output reg [31:0] rt_out;
output reg [5:0] rd_out;

output reg [31:0] adder_out;

always@ (posedge clk)
begin 
    // inputs to outputs
    reg_wrt_out = reg_wrt;
    mem_to_reg_out = mem_to_reg;
    pc_to_reg_out = pc_to_reg;
    branch_neg_out = branch_neg;
    branch_Zero_out = branch_Zero;
    jump_out = jump;
    jump_mem_out = jump_mem;
    ALU_op_out = ALU_op;
    mem_rd_out = mem_rd;
    mem_wrt_out = mem_wrt;

    rs_out = rs;
    rt_out = rt;
    rd_out = rd;

    adder_out = adder;
end
endmodule
