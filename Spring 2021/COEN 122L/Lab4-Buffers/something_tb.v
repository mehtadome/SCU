`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/06/2021 02:11:36 PM
// Design Name: 
// Module Name: something_tb
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


module something_tb();

    // clock, one register and 3 wires
    reg clk;
    reg [31:0] IF;
    wire [31:0] ID;
    wire [31:0] EX;
    wire [31:0] WB;
	
    //test cases
    IFID test_ifid (clk, IF,IF,ID,ID);
    IDEX test_idex (clk, ID,ID,ID,ID,ID,ID,ID,ID,ID,ID,ID,ID,ID,ID, EX,EX,EX,EX,EX,EX,EX,EX,EX,EX,EX,EX,EX,EX);
    EXMEMWB test_exwb (clk, EX,EX,EX,EX,EX,EX,EX,EX,EX,EX,EX,EX,EX, WB,WB,WB,WB,WB,WB,WB,WB,WB,WB,WB,WB,WB);
    
    // clock code
    initial
    begin 
        clk = 0;
        forever #5 clk = ~clk;
    end
    
    // just change the statement around
    initial
    begin 
        IF = 1;
        #50;
        
        IF = 2;
        #50;
        
        IF = 3;
        #50;
        
        IF = 4;
        #50
        
        IF = 5;
        #50
    $finish;
    end
endmodule
