// Author: Ratnodeep Bandyopadhyay. Copyright 2021.

module round #(parameter INTW=10, parameter RATW=10) (
        
        input [INTW+(2*RATW)-1:0] in,
        output wire [INTW+RATW-1:0] out
    );

    assign out = in[INTW+RATW-1:RATW] + in[RATW-1];

endmodule
