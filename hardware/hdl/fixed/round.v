// Author: Ratnodeep Bandyopadhyay. Copyright 2021.

module fixed_round #(parameter INT_WID=10, parameter RAT_WID=10) (
        
        input clk,
        input [(INT_WID+RAT_WID-1):0] x,
        output reg [(INT_WID+RAT_WID-1):0] xr

    );

    wire [INT_WIDTH-1:0] round_up_const;

    assign round_up_const = {(INT_WIDTH-1){0}, {x[RAT_WIDTH+1]}};
    
    always @(posedge clk) begin
        xr <= {{x[INT_WID+RAT_WID-1:RAT_WID] + round_up_const}, (RAT_WID){0});
    end

endmodule
