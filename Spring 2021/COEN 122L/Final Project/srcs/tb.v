`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/27/2021 10:56:21 PM
// Design Name: 
// Module Name: tb
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


module tb();

// Clock
reg clk;

// 1st 2to1mux
wire branch_or_out; // branch OR (brn_cond_out AND branch)
wire [31:0] mux_pcSrc2_out;

// Program Counter wires
wire [31:0] address; 

// Adder Wires
wire [31:0] adder_out;

// Instruction Memory Wires
wire [31:0] instruction_mem_out;

// IF/ID Buffer Wires
wire [31:0] ifid_pc_out;
wire [31:0] ifid_instruction_out;

// Sign Extender wires 
wire [31:0] sign_out;

// Registers Wires
wire [31:0] rs_out, rt_out;

// Control  Wires
wire cntrl_reg_wrt, cntrl_mem_to_reg, cntrl_branch, cntrl_brn_cond, cntrl_pc_src, cntrl_mem_read, 
cntrl_mem_wrt;
wire [3:0] cntrl_ALU_Op;
wire [1:0] cntrl_ALU_Src;

// ID/EX-MEM Buffer Wires
wire idex_reg_wrt_out, idex_mem_to_reg_out, idex_branch_out, idex_brn_cond_out, 
idex_pc_src_out, idex_mem_read_out, idex_mem_wrt_out;

wire [3:0] idex_ALU_Op_out;
wire [1:0] idex_ALU_Src_out;

wire [31:0] idex_pc_out;

wire [31:0] idex_rs_out, idex_rt_out;

wire [31:0] idex_immediate_out;

wire [5:0] idex_rd_out;

// ALUSrc1 mux 
wire [31:0] ALUSrc1_out;

// ALUSrc2 mux 
wire [31:0] ALUSrc2_out;

// ALU 
wire [31:0] ALU_out; 
wire ALU_zero_out;
wire ALU_neg_out;

// Data Memory Wires
wire [31:0] data_mem_out;

// PC_Src Mux 
wire [31:0] pc_src_mux_out; 

// EX-MEM/WB Buffer Wires
wire exwb_reg_wrt_out, exwb_mem_to_reg_out;
wire exwb_branch_out, exwb_brn_cond_out, exwb_pc_src_mux_out;
wire exwb_ALU_zero_out, exwb_ALU_neg_out;
wire [31:0] exwb_ALU_out;
wire [31:0] exwb_data_mem_out;
wire [5:0] exwb_rd_out;

// Brn_Cond Mux 
wire brn_cond_mux_out; 

// AND Gate for brn_cond and branch 
wire brn_cond_and_branch_out; 

// Mem_to_reg mux 
wire [31:0] mem_to_reg_mux_out;


// Logic 

// OR Gate logic 
ORGate myOr(idex_branch_out, brn_cond_and_branch_out, branch_or_out);

mux pcSrc2(adder_out, pc_src_mux_out, branch_or_out, mux_pcSrc2_out);

pc program_counter(clk, mux_pcSrc2_out, address);

adder myadder(address, 1, adder_out);



instruction_memory inst_mem(clk, address, instruction_mem_out);



IFID ifid_buf(clk, address, instruction_mem_out, ifid_pc_out, ifid_instruction_out);

register_file register(clk, exwb_reg_wrt_out, mem_to_reg_mux_out, ifid_instruction_out[21:16], 
ifid_instruction_out[15:10], exwb_rd_out, rs_out, rt_out);

sign_extend         signExtend(ifid_instruction_out[31:0], sign_out);

control             control_unit(clk, ifid_instruction_out[31:28], cntrl_reg_wrt, cntrl_mem_to_reg, 
cntrl_ALU_Op, cntrl_ALU_Src, cntrl_branch, cntrl_brn_cond, cntrl_pc_src);



// ID / EX-MEM logic      |   (clk, reg_wrt, mem_to_reg, ALU_Op, alu_src, branch, brn_cond, pc_src, mem_rd, mem_wrt, pc_in,
// rs, rt, instrs, immediate, rd, 
// reg_wrt_out, mem_to_reg_out, ALU_Op_out, alu_src_out, branch_out, brn_cond_out, pc_src_out, mem_rd_out, mem_wrt_out,
// idex_pc_out, rs_out, rt_out, immediate_out, rd_out)

IDEX                idex_buffer(clk, cntrl_reg_wrt, cntrl_mem_to_reg, cntrl_ALU_Op, cntrl_ALU_Src, 
cntrl_branch, cntrl_brn_cond, cntrl_pc_src, cntrl_mem_read, cntrl_mem_wrt, 
ifid_pc_out, rs_out, rt_out, sign_out,  ifid_instruction_out[27:22], 
idex_reg_wrt_out, idex_mem_to_reg_out, idex_ALU_Op_out, idex_ALU_Src_out, idex_branch_out, idex_brn_cond_out, 
idex_pc_src_out, idex_mem_read_out, idex_mem_wrt_out, idex_pc_out, idex_rs_out, idex_rt_out, idex_immediate_out, 
idex_rd_out);

// ALUSrc1 mux logic    |   (A, B, sel, out)
mux                 ALU_Src1(idex_rs_out, idex_pc_out, idex_ALU_Src_out[1], ALUSrc1_out);

// ALUSrc2 mux logic    |   (A, B, sel, out)
mux                 ALU_Src2(idex_rt_out, idex_immediate_out, idex_ALU_Src_out[0], ALUSrc2_out);

// Data Memory logic    |   (clk, wrt, read, address, data_in, data_out)
data_memory         data_mem(clk, idex_mem_wrt_out, idex_mem_read_out, idex_rs_out, idex_rt_out, data_mem_out);

// ALU logic    |   (A, B, sel, out, neg, zero)
alu                 myALU(ALUSrc1_out, ALUSrc2_out, idex_ALU_Op_out, ALU_out, ALU_neg_out, ALU_zero_out);

// PC_Src Mux logic         |   (A, B, sel, out)
mux                 pc_src_mux(idex_rs_out, data_mem_out, idex_pc_src_out, pc_src_mux_out);

// EX-MEM/WB logic      |   (clk, reg_wrt, mem_to_reg, idex_branch, idex_brn_cond, pc_src_out, ALU_zero, ALU_neg, ALU, data_mem, rd, 
// reg_wrt_out, mem_to_reg_out, exwb_branch_out, exwb_brn_cond_out, exwb_pc_src_out, ALU_zero_out, ALU_neg_out, ALU_out, 
// data_mem_out, rd_out)
EXMEMWB             exmemwb_buffer(clk, idex_reg_wrt_out, idex_mem_to_reg_out, idex_branch_out, idex_brn_cond_out,
pc_src_mux_out, ALU_zero_out, ALU_neg_out, ALU_out, data_mem_out, idex_rd_out, 
exwb_reg_wrt_out, exwb_mem_to_reg_out, exwb_branch_out, exwb_brn_cond_out, exwb_pc_src_out, exwb_ALU_zero_out, exwb_ALU_neg_out, exwb_ALU_out, 
exwb_data_mem_out, exwb_rd_out);

// Brn_Cond mux logic       |   (A, B, sel, out)
mux                 brn_cond_mux(exwb_ALU_zero_out, exwb_ALU_neg_out, exwb_brn_cond_out, brn_cond_mux_out);

// AND Gate logic 
ANDGate             myAnd(brn_cond_mux_out, exwb_branch_out, brn_cond_and_branch_out);

// Mem to Reg Mux logic       |   (A, B, sel, out)
mux                 memToRegMux(exwb_ALU_out, exwb_data_mem_out, exwb_mem_to_reg_out, mem_to_reg_mux_out);

initial begin
    clk = 0;
    forever #10 clk = ~clk;
end

initial begin
    
    #500;
    $finish;
end
endmodule
