`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/27/2021 12:38:44 PM
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


module EXMEMWB(clk, reg_wrt, mem_to_reg, idex_branch, idex_brn_cond, pc_src_out, ALU_zero, ALU_neg, ALU, data_mem, rd, 
reg_wrt_out, mem_to_reg_out, exwb_branch_out, exwb_brn_cond_out, exwb_pc_src_out, ALU_zero_out, ALU_neg_out, ALU_out, 
data_mem_out, rd_out);

// Clock 
input clk;

// ID/EX outputs
input reg_wrt;
input mem_to_reg;

// Branch 
input idex_branch;
input idex_brn_cond;

// PC_Src Mux  
input pc_src_out;

// ALU
input ALU_zero;
input ALU_neg; 
input [31:0] ALU; 

// Data Memory out
input [31:0] data_mem;

// rd
input [5:0] rd;

// outputs
output reg reg_wrt_out;
output reg mem_to_reg_out;

output reg exwb_branch_out;
output reg exwb_brn_cond_out;

output reg exwb_pc_src_out

output reg ALU_zero_out;
output reg ALU_neg_out;
output reg [31:0] ALU_out;

output reg [31:0] data_mem_out;
output reg [5:0] rd_out;


always@ (posedge clk)
begin 
    // inputs to outputs

    reg_wrt_out = reg_wrt;
    mem_to_reg_out = mem_to_reg;

    exwb_branch_out = idex_branch;
    exwb_brn_cond_out = idex_brn_cond;

    exwb_pc_src_out = pc_src_out;

    ALU_zero_out = ALU_zero;
    ALU_neg_out = ALU_neg;
    ALU_out = ALU;

    data_mem_out = data_mem;
    rd_out = rd;
     
end
endmodule
