`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/30/2021 03:18:07 PM
// Design Name: 
// Module Name: tb_datamem
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

// clk, wrt, read, address, data_in, data_out
module tb_datamem();

    reg clk;
    reg write;
    reg read;
    
    reg [31:0] address;
    reg [31:0] data_in;
    wire [31:0] data_out; 
    
    // call function to test
    data_memory tb_datamem(clk, write, read, address, data_in, data_out);
    
    initial
    begin
        clk = 0;
        forever #5 clk = ~clk;
    end  
    
    
    // testing block
    initial 
    begin 
        write = 1; 
        read = 0;
        address = 3;
        data_in = 4;
        #50 
        write = 0;
        read = 1;
        #50
        $finish;
    end


endmodule
