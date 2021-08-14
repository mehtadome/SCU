module ORGate(A, B, out);
    // inputs
    input A; 
    input B;
    // outputs
    output reg out; 
    always@(A, B)begin
        out = A || B;
    end

endmodule