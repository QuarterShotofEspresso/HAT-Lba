// Author: Ratnodeep Bandyopadhyay. Copyright 2022.
//void rat_mul_rat(struct rational* l, struct rational* r, struct rational* s) {
//    s->num = l->num * r->num;
//    s->den = l->den * r->den;
//    return;
//}


module mul #(parameter WIDTH=32) (
        // CLK
        input clk,
        // META IN
        input enable_div,
        // DATA IN
        input [WIDTH-1:0] l_num,
        input [WIDTH-1:0] l_den,
        input [WIDTH-1:0] r_num,
        input [WIDTH-1:0] r_den,
        // DATA OUT
        output reg [WIDTH-1:0] s_num,
        output reg [WIDTH-1:0] s_den
    );

    always @(posedge clk) begin
        s_num <= l_num * ((enable_div) ? r_den : r_num);
        s_den <= l_den * ((enable_div) ? r_num : r_den);
    end

endmodule
