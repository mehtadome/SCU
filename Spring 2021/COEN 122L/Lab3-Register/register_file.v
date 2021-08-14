module register_file(read_addr_1, read_addr_2, write_adder,
write_data, reg_write, CLK, read_data_1, read_data_2);

    input [5:0] read_addr_1;
    input [5:0] read_addr_2;
    input [5:0] write_adder;
    input [31:0] write_data;

    input reg_write;
    input CLK;
    output reg [31:0] read_data_1, read_data_2;

    integer i;
    reg [31:0] registers [63:0];

    initial 
        begin
        for (i = 0; i < 64; i = i + 1) begin 
            registers[i] = i;
        end 
    end

    always@(posedge CLK)
    begin 
        read_data_1 = registers[read_addr_1];
        read_data_2 = registers[read_addr_2];

        if (reg_write == 1)
            registers[write_addr] = write_data;
    end 

endmodule

