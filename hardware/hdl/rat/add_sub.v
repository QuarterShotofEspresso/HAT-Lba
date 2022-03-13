// Author: Ratnodeep Bandyopadhyay Copyright. 2021
//void rat_add_rat(struct rational* l, struct rational* r, struct rational* s) {
//    
//    if(l->den == r->den) {
//        s->num = l->num + r->num;
//        s->den = l->den;
//    } else {
//        s->num = (l->num * r->den) + (r->num * l->den);
//        s->den = l->den * r->den;
//    }
//
//    return;
//}

module add_sub #(parameter WIDTH=32) (
        input clk,
        // META IN
        input rst,
        input enable_sub,
        // DATA IN
        input [WIDTH-1:0] l_num,
        input [WIDTH-1:0] l_den,
        input [WIDTH-1:0] r_num,
        input [WIDTH-1:0] r_den,
        
        // DATA OUT
        output reg [WIDTH-1:0] s_num,
        output reg [WIDTH-1:0] s_den,
        // META OUT
        output wire rdy_out
    );

    // internal registers
    reg [WIDTH-1:0] temp_1;
    reg [WIDTH-1:0] temp_2;
    reg [WIDTH-1:0] temp_3;

    reg reg_rdy_1a;
    reg reg_rdy_2a;
    
    // wire assignments
    assign rdy_out = reg_rdy_2a;
   
    // RESET Logic
    always @(posedge rst) begin
        reg_rdy_1a <= 0;
        reg_rdy_2a <= 0;

        temp_1 <= 0;
        temp_2 <= 0;
        temp_3 <= 0;
    end

    always @(posedge clk) begin
        // CLK 1
        temp_1 <= l_num * r_den;
        temp_2 <= l_den * r_num;
        temp_3 <= l_den * r_den;
        reg_rdy_1a <= 1'b1;

        // CLK 2
        s_num <= temp_1 + ((enable_sub) ? -temp_2 : temp_2);
        s_den <= temp_3;
        reg_rdy_2a <= reg_rdy_1a;
    end

endmodule
