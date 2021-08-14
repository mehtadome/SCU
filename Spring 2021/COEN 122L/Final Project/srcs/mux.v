`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// School: Santa Clara University, Department of Engineering
// Engineer: Ruchir Mehta and Vasilis Odysseos 
// 
// Create Date: 04/22/2021 12:33:32 PM
// Module Name: mux
// Project Name: COEN 122: Computer Architecture Max Calculation
// Additional Comments:
// 
//
//
//////////////////////////////////////////////////////////////////////////////////


module mux(A, B, sel, out);
input [31:0] A;
input [31:0] B;
input sel;
output reg [31:0] out;

always@(A, B, sel)
// depending on what the select is
begin
    out = A;
    if(sel == 1) 
      out = B;
end

endmodule
