module top(
    input clk,             // Clock
    input rst,             // Reset
    input cyc,             // Cycle valid
    input stb,             // Strobe (indicates valid data)
    input we,              // Write Enable (1 for write, 0 for read)
	input [3:0] wb_sel,    // Byte select (for writes)
    input [31:0] adr,      // Address
    input [31:0] dat_mosi, // Data from master to slave
    output reg [31:0] dat_miso, // Data from slave to master
    output ack,            // Acknowledge from slave
    output err             // Error from slave
);

    // Declare the register
    reg [31:0] my_register;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            my_register <= 32'b0;
            dat_miso <= 32'b0;
        end else if (cyc && stb) begin
            if (we) begin
                my_register <= dat_mosi;
            end
            dat_miso <= adr;
        end
    end

    // For simplicity, we'll just always acknowledge and never error.
    assign ack = cyc && stb;
    assign err = 1'b0;

endmodule