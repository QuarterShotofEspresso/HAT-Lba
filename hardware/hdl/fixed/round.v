// Author: Ratnodeep Bandyopadhyay. Copyright 2021.

module round #(parameter INTW=10, parameter RATW=10) (
        
        input [(INTW+(2*RATW))-1:0] in,
        output wire [INTW+RATW-1:0] out
    );

    wire [INTW-1:1] round_int0;
    wire [RATW:0] round_rat0;
    wire [INTW+RATW-1:0] round_const = {round_int0, x[RATW], round_rat0};

    assign round_int0 = 0;
    assign round_rat0 = 0;
    assign out = in[INTW+RATW-1:0] + round_const;

endmodule
