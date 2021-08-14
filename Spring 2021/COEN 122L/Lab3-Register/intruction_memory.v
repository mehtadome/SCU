`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/29/2021 03:37:07 PM
// Design Name: 
// Module Name: instruction_memory
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


module instruction_memory(clk, address, inst);
//initialization of variables
input clk;
input [31:0] address;
output reg [31:0] inst;
wire[31:0] instructions[255:0];

// assign a specific instruction
assign instructions[0] = 10; 
assign instructions[1] = 11;

always@(posedge clk)
begin
    inst = instructions[address]; //read instructions[i] 
end
endmodule
