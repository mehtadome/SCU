`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/27/2021 12:03:33 PM
// Design Name: 
// Module Name: control
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

module control(clk, opcode, reg_wrt, mem_to_reg, ALU_Op, ALU_Src, branch, brn_cond, PC_Src, 
Mem_Read, Mem_Write);

input [3:0] opcode; // inst [31-28]
input clk;

// registers
output reg reg_wrt, mem_to_reg, branch, brn_cond, PC_Src, Mem_Read, Mem_Write;
// alu op code
output reg [3:0] ALU_Op; 
output reg [1:0] ALU_Src;

always@(posedge clk)
begin
   
    // set all to 0 
    ALU_Op = 4'b0111;   // Pass A
    reg_wrt = 0;
    mem_to_reg = 0;
    branch = 0;
    brn_cond = 0;   // branch zero or branch neg
    PC_Src = 0;
    Mem_Read = 0;
    Mem_Write = 0;
    
    // No operator
    if (opcode == 4'b0000)
        // everything remains 0
    
    // SavePC
    if (opcode == 4'b1111)
    begin
        ALU_Op = 4'b0100;
        ALU_Src = 2'b11;
        reg_wrt = 1;
    end
    
    // Load
    if (opcode == 4'b1110)
    begin
        reg_wrt = 1;
        mem_to_reg = 1;
        Mem_Read = 1;
    end
    
    // Store 
    if (opcode == 4'b0011) 
        Mem_Write = 1;
    
    // Add 
    if (opcode == 4'b0100)
    begin
        ALU_Op = 4'b0100;
        ALU_Src = 2'b00;
        reg_wrt = 1;
    end
    
    // Increment
    if (opcode == 4'b0101) 
    begin
        ALU_Op = 4'b0100;
        ALU_Src = 2'b01;
        reg_wrt = 1;
    end
    
    // Negate
    if (opcode == 4'b0110)
    begin
        ALU_Op = 4'b0010;
        ALU_Src = 2'b01; // last bit doesn't matter 
        reg_wrt = 1;
    end
    
    // Subtract 
    if (opcode == 4'b0111)
    begin
        ALU_Op = 4'b0001; 
        ALU_Src = 2'b00;
        reg_wrt = 1;
    end
    
    // Jump
    if (opcode == 4'b1000)
        branch = 1;
    
    // Branch Condition 0
    if (opcode == 4'b1001)
    begin
        branch = 1;
        brn_cond = 0;
    end
    
    // Jump Memory
    if (opcode == 4'b1010)
    begin
        Mem_Read = 1;
        branch = 1;
        PC_Src = 1;
    end
    
    // Branch Condition <0
    if (opcode == 4'b1011)
    begin
        branch = 1;
        brn_cond = 1;
    end
end

endmodule 
