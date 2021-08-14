`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/27/2021 12:00:32 PM
// Design Name: 
// Module Name: ANDGate
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

module ANDGate(A, B, out);
    // inputs
    input A; 
    input B;
    // outputs
    output out; 

    assign out = A & B;

endmodule


