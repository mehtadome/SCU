`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/27/2021 12:15:39 PM
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


// clk, sel, write data, read_reg1, read_reg2, write_reg, read_data1, read_data2
module register_file(clk, writer, input_data, reg_source, reg_target, reg_destination, write_source_out, write_target_out);

//initialization of variables
input clk;

// reg_wrt
input writer;

// read_reg_1
input[5:0] reg_source;
// read_reg_2
input[5:0] reg_target;

// write_reg
input[5:0] reg_destination;
// write_data
input [31:0] input_data;

reg[31:0] registers[63:0];

// rs
output reg [31:0] write_source_out;
// rd
output reg [31:0] write_target_out;

initial begin 
    registers[0] = 0;
    registers[2] = 0;
    registers[3] = 20;
   end

always@(posedge clk)
begin
    if (writer == 1) //
        registers[reg_destination] = input_data;
        
    write_source_out = registers[reg_source]; 
    write_target_out = registers[reg_target];
end
endmodule
