`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Ruchir Mehta
// 
// Create Date: 04/21/2021 10:58:36 AM
// Design Name: ALU Testbanch
// Module Name: alu
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: Create an ALU testbench to run simulation
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module aluTest();

// establish inputs
reg [31:0] A;
reg [31:0] B;
reg [3:0] opcode;

// establish wires
wire [31:0] res;
wire neg;
wire zero;

// call the method
alu test(A,B,opcode,res,neg,zero);

initial
begin
	// addition
	A = 0;
	B = 1;
	opcode = 4'b0000;
	#50 // tells verilog to wait 50ns
	A = 1;
	B = 0;
	opcode = 4'b0000;
	#50
	A = 1;
	B = 1;
	opcode = 4'b0000;
	#50
	A = 2;
	B = 2;
	opcode = 4'b0000;
	#50
	
	// increment
	A = 0;
	B = 1;
	opcode = 4'b0001;
	#50
	A = 1;
	B = 0;
	opcode = 4'b0001;
	#50
	A = 1;
	B = 1;
	opcode = 4'b0001;
	#50
	A = 2;
	B = 2;
	opcode = 4'b0001;
	#50
	
	// 2's compliment
	A = 0;
	B = 1;
	opcode = 4'b0010;
	#50
	A = 1;
	B = 0;
	opcode = 4'b0010;
	#50
	A = 1;
	B = 1;
	opcode = 4'b0010;
	#50
	A = 2;
	B = 2;
	opcode = 4'b0010;
	#50
	
	// subtracting
	A = 0;
	B = 1;
	opcode = 4'b0011;
	#50
	A = 1;
	B = 0;
	opcode = 4'b0011;
	#50
	A = 1;
	B = 1;
	opcode = 4'b0011;
	#50
	A = 2;
	B = 2;
	opcode = 4'b0011;
	#50
	
	// pass A
	A = 0;
	B = 1;
	opcode = 4'b0100;
	#50
	A = 1;
	B = 0;
	opcode = 4'b0100;
	#50
	A = 1;
	B = 1;
	opcode = 4'b0100;
	#50
	A = 2;
	B = 2;
	opcode = 4'b0100;
	#50
$finish;

end 
endmodule