`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/29/2021 03:37:29 PM
// Design Name: 
// Module Name: register_file
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

// test by write flag to one
// set register destination to different input data
// read from the registers outputted to after writing

module register_file(clk, writer, input_data, reg_source, reg_target, reg_destination, write_source_out, write_target_out);
//initialization of variables
input clk;
input writer;

//register source, register target, and register destination
input[5:0] reg_source;
input[5:0] reg_target;
input[5:0] reg_destination;

input [31:0] input_data;

reg[31:0] registers[63:0];

output reg [31:0] write_source_out;
output reg [31:0] write_target_out;

always@(posedge clk)
begin
    if (writer == 1) //
        registers[reg_destination] = input_data;
        
    write_source_out = registers[reg_source];
    write_target_out = registers[reg_target];
end
endmodule
