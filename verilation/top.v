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

parameter A_OFFSET = 0;    // Start address for matrix A
parameter B_OFFSET = 9;    // Start address for matrix B
parameter C_OFFSET = 18;   // Start address for matrix C
parameter MAT_SIZE = 9;    // Size for matrices A, B, and C
parameter INT_WIDTH = 8; // Size for matrices A, B, and C

// inputs
reg [71:0] A, B;
reg Enable;
reg reset_matrix;
// outputs
wire [71:0] C;
wire done;

matrix_mult mm_inst(
    .Clock(clk),
    .reset(reset_matrix),
    .Enable(Enable),
    .A(A),
    .B(B),
    .C(C),
    .done(done)
);

always @(posedge clk or posedge rst) begin
    if (rst) begin
        dat_miso <= 32'b0;
        ack <= 0;
        err <= 0;
        reset_matrix <= 1;
        Enable <= 0;
        A <= 72'b0;
        B <= 72'b0;
    end else if (cyc && stb) begin
        ack <= 0;
        err <= 0;
        reset_matrix <= 0;

        if (we && wb_sel[0]) begin
            reset_matrix <= 1;
            // Write to A or B
            if (adr < A_OFFSET+MAT_SIZE) begin
                A[((adr-A_OFFSET)*INT_WIDTH)+:INT_WIDTH] <= dat_mosi[7:0];
                ack <= 1;
            end else if (adr >=B_OFFSET && adr < B_OFFSET+MAT_SIZE) begin
                B[((adr-B_OFFSET)*INT_WIDTH)+:INT_WIDTH] <= dat_mosi[7:0];
                ack <= 1;
            end else begin
                err <= 1;
            end
        end else if (!we) begin
            // Asking to read from C
            if (adr >= C_OFFSET && adr < C_OFFSET+MAT_SIZE) begin
                // Start the calculation
                Enable <= 1;
                // done lets us know when the calculation is done
                if (done) begin
                    // Calculation is done, read from C
                    dat_miso[7:0] <= C[(adr-C_OFFSET)*INT_WIDTH+:INT_WIDTH];
                    ack <= 1;
                    // Clear the enable after reading is done
                    Enable <= 0;
                end
            end else begin
                err <= 1;
            end
        end
    end else begin
        ack <= 0;
        err <= 0;
    end
end

endmodule