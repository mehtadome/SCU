`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/30/2021 03:17:23 PM
// Design Name: 
// Module Name: tb_instruction
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

// instruction_memory(clk, address, inst);
module tb_instruction();

    reg clk;
    reg [31:0] address;
    wire [31:0] instruction;
    
    instruction_memory tb_instruction(clk, address, instruction);

    initial
    begin
        clk = 0;
        forever #5 clk = ~clk;
    end 

    initial 
    begin
        address = 0;
        #50
        address = 1;
        
        #50
        $finish;
    end

endmodule
