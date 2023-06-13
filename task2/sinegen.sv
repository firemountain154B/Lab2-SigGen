module sinegen #(
    parameter   A_WIDTH = 8,
                D_WIDTH = 8
)(
    // interface signals 
    input logic                 clk,
    input logic                 rst, 
    input logic                 en, 
    input logic [D_WIDTH-1:0]   incr, // increment for address counter
    output logic [D_WIDTH-1:0]  dout1,
    output logic [D_WIDTH-1:0]  dout2
);

    logic [A_WIDTH - 1:0]       address1;
    logic [A_WIDTH - 1:0]       address2;

    assign address2 = address1 + 8'd64;
counter #(
    .WIDTH(D_WIDTH)
)addrCounter(
    .clk(clk),
    .rst(rst),
    .en(en),
    .incr(incr),
    .count(address1)
);

dual_rom #(
    .ADDRESS_WIDTH(A_WIDTH),
    .DATA_WIDTH(D_WIDTH)
)dual_sineRom(
    .clk(clk),
    .addr1(address1),
    .addr2(address2),
    .dout1(dout1),
    .dout2(dout2)
);

endmodule
