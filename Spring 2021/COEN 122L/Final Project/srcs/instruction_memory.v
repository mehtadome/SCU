`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/27/2021 12:11:38 PM
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
assign instructions[0] = 32'sb01010001000000001000000000000000;
assign instructions[1] = 32'sb01000001010000100000110000000000;
assign instructions[2] = 32'sb01010001010001011111110000000000;
assign instructions[3] = 32'sb11110010010000000000100000000000;
assign instructions[4] = 32'sb11110010100000000001010000000000;
assign instructions[5] = 32'sb11100001100000100000000000000000;
assign instructions[6] = 32'sb01110001110001100001000000000000; 
assign instructions[7] = 32'sb10110000000010100000000000000000;
assign instructions[8] = 32'sb01000001000001100000000000000000;
assign instructions[9] = 32'sb01010000100000100000010000000000;
assign instructions[10] = 32'sb01110010000000100001010000000000;
assign instructions[11] = 32'sb10110000000010010000000000000000;


always@(posedge clk)
begin
    inst = instructions[address]; //read instructions[i] 
end
endmodule
