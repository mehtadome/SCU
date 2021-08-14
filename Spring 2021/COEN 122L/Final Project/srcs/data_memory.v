`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/27/2021 12:10:52 PM
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


module data_memory(clk, wrt, read, address, data_in, data_out);

//initialization of variables
input clk;

// mem_wrt
input wrt;
// mem_read
input read;

reg [31:0] data[65535:0];

// address
input [31:0] address;
// data_in
input [31:0] data_in;

// out
output reg [31:0] data_out;

initial begin
    data[0] = 20123;
    data[1] = 18833;
    data[2] = 39041;
    data[3] = -16424;
    data[4] = 36453;
    data[5] = 11705;
    data[6] = -49943;
    data[7] = 58325;
    data[8] = -35654;
    data[9] = -37822;
    data[10] = -2700;
    data[11] = 2050;
    data[12] = 46716;
    data[13] = -40214;
    data[14] = -19144;
    data[15] = -26370;
    data[16] = -17979;
    data[17] = -26735;
    data[18] = -29557;
    data[19] = 14800;
end

always@(posedge clk)
begin
     // put data into output
     if (read == 1) 
          data_out = data[address[15:0]];

     // writing data from the address to data[i]
     else if (wrt == 1) 
          data[address[15:0]] = data_in;
end
endmodule

