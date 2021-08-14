`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/29/2021 03:37:52 PM
// Design Name: 
// Module Name: data_memory
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

// write something to an address
// then read from writed-to address

module data_memory(clk, wrt, read, address, data_in, data_out);
//initialization of variables
input clk;
input wrt;
input read;
reg [31:0] data[65535:0];

input [31:0] address;
input [31:0] data_in;

output reg [31:0] data_out;

always@(posedge clk)
begin
   if (read == 1) //put data into output
        data_out = data[address[15:0]];
   else if (wrt == 1) //writing data from the address to data[i]
        data[address[15:0]] = data_in;
end
endmodule
