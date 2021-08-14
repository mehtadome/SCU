`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/22/2021 12:31:28 PM
// Design Name: 
// Module Name: adder32bit
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

module adder(A, B, out);
  input [31:0] A, B;  
  output reg [31:0] out;    
  
  // Adder Operation
  always @(A, B) begin
    out = A + B;
  end
  
endmodule
