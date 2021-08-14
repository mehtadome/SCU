`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/30/2021 03:16:45 PM
// Design Name: 
// Module Name: tb_register
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

// register_file(clk, writer, input_data, reg_source, reg_target, reg_destination, write_source_out, write_target_out);
module tb_register();
    
    reg clk;
    reg write;
    
    reg [31:0] address;
    
    reg [5:0] reg_source;
    reg [5:0] reg_target;
    reg [5:0] reg_destination; 
    
    reg [31:0] data_in;
    
    wire [31:0] write_source_out;
    wire [31:0] write_target_out;

    register_file tb_register(clk, write, data_in, reg_source, reg_target, reg_destination, write_source_out, write_target_out);

    initial
    begin
        clk = 0;
        forever #5 clk = ~clk;
    end 
    
    initial
    begin
        write = 1; 
        data_in = 5;
        reg_destination= 5; 
        
        #50 
        data_in = 6;
        reg_destination = 6;
        
        #50 
        write = 0;
        reg_source = 5;
        reg_target = 6;
        
        #50
        $finish;
    
    end


endmodule
