// Author: Ratnodeep Bandyopadhyay. Copyright 2022.

//int mod_div(struct rational* x) {
//
//    // move negative to the numerator
//    if(x->den < 0) {
//        x->num = -x->num;
//        x->den = -x->den;
//    }
//
//    int quo = x->num / x->den;
//    int mod = x->num % x->den;
//
//    if(mod >= (x->den / 2)) {
//        return quo + 1;
//    } else {
//        return quo;
//    }
//}

module mod_div #(parameter WIDTH=32) (
        // META IN
        input rst,
        // DATA IN
        input [WIDTH-1:0] num,
        input [WIDTH-1:0] den,
        // DATA OUT
        output reg [WIDTH-1:0] out,
        // META OUT
        output wire rdy_out
    );

    reg [WIDTH-1:0] tmp_num;
    reg [WIDTH-1:0] tmp_den;

    reg [WIDTH-1:0] quo;
    reg [WIDTH-1:0] rem;

    reg reg_rdy_a;
    reg reg_rdy_b;
    reg reg_rdy_c;

    wire den_is_neg;
    wire [WIDTH-1:0] round_up;

    assign den_is_neg = den[WIDTH-1];
    assign [WIDTH-1:0] round_up = {{(WIDTH-2)'b0},{rem >= (tmp_den >> 1)}};
    assign rdy_out = reg_rdy_c;

    always @(posedge rst) begin
        out <= 0;
        tmp_num <= 0;
        tmp_den <= 0;
        quo <= 0;
        rem <= 0;
        reg_rdy_a <= 0;
        reg_rdy_b <= 0;
        reg_rdy_c <= 0;
    end

    always @(posedge clk) begin
        // CLK 1
        tmp_num <= (den_is_neg) -num : num;
        tmp_den <= (den_is_neg) -den : den;
        reg_rdy_a <= 1;

        // CLK 2
        quo <= tmp_num / tmp_den;
        rem <= tmp_num % tmp_den;
        reg_rdy_b <= reg_rdy_a;

        // CLK 3
        out <= quo + round_up;
        reg_rdy_c <= reg_rdy_b;
    end

endmodule
