`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/27/2021 12:17:20 PM
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


module IDEX(clk, reg_wrt, mem_to_reg, ALU_Op, alu_src, branch, brn_cond, pc_src, mem_rd, mem_wrt, pc_in,
rs, rt, immediate, rd, 
reg_wrt_out, mem_to_reg_out, ALU_Op_out, alu_src_out, branch_out, brn_cond_out, pc_src_out, mem_rd_out, mem_wrt_out, pc_out,
rs_out, rt_out, immediate_out, rd_out);

// inputs
input clk;
input reg_wrt;
input mem_to_reg;
input [3:0] ALU_Op;
input [1:0] alu_src;
input branch;
input brn_cond;
input pc_src;
input mem_rd;
input mem_wrt;
input [31:0] pc_in;
input [31:0] rs; // register output 1
input [31:0] rt; // register output 2
//input [32:0] instrs; // instr[9-0] **
input [31:0] immediate; // immediate generator
input [5:0] rd; // IF/ID

// outputs
output reg reg_wrt_out;
output reg mem_to_reg_out;
output reg [3:0] ALU_Op_out;
output reg [1:0] alu_src_out;
output reg branch_out;
output reg brn_cond_out;
output reg pc_src_out;
output reg mem_rd_out;
output reg mem_wrt_out;
output reg [31:0] pc_out;
output reg [31:0] rs_out;
output reg [31:0] rt_out;
output reg [31:0] immediate_out;
output reg [5:0] rd_out;

always@ (posedge clk)
begin 
    // inputs to outputs
    reg_wrt_out = reg_wrt;
    mem_to_reg_out = mem_to_reg;
    ALU_Op_out = ALU_Op;
    alu_src_out = alu_src;
    branch_out = branch;
    brn_cond_out = brn_cond;
    pc_src_out = pc_src;
    mem_rd_out = mem_rd;
    mem_wrt_out = mem_wrt;
    pc_out = pc_in;
    rs_out = rs;
    rt_out = rt;
    immediate_out = immediate;
    rd_out = rd;
end

endmodule

