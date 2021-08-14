module sign_extend(data_in, data_out);

// inst[31:0]
input [31:0] data_in;

// immediate
output reg [31:0] data_out;

// 
always@(data_in)
begin
    data_out = 0;
    if(data_in[31:28] == 4'b1111)
    begin
        data_out[31:0] = { {20{data_in[21]}}, data_in[21:10]};
    end
    
    if(data_in[31:28] == 4'b0101)
    begin
        data_out[31:0] = { {26{data_in[15]}}, data_in[15:10]};
        //data_out[31:6] = data_in[15];
        //data_out[5:0] = data_in[15:10];
    end
   
    
end
endmodule