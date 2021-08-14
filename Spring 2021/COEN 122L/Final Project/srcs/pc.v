`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/27/2021 12:13:41 PM
// Design Name: 
// Module Name: pc
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


module pc(clock, in, address);

input clock;
input [31:0] in;
output reg [31:0] address;

initial begin
    #15;
    address[31:0] = 0;
    
    
end
always@(posedge clock)
begin
    if(in)
        address = in;
end
endmodule