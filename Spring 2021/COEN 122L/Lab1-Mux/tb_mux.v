`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/15/2021 05:00:57 PM
// Design Name: 
// Module Name: tb_mux
// Project Name: Lab1
// Target Devices: 
// Tool Versions: 
// Description: Testbench for a 4:1 multiplexer
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

// define the module
module tb_mux();
// variable creation
reg D1,D2,D3,D4;
reg [1:0] sel;
// create out wire
wire out;
mux test(D1,D2,D3,D4,sel,out);

initial
begin
    D1=1;
    D2=0;
    D3=0;
    D4=1;
    // wait 50 ns per assignment
    sel = 2'b00;
    #50
    sel = 2'b01;
    #50
    sel = 2'b10;
    #50
    sel = 2'b11;
    #50
$finish;
end

endmodule
