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

module add #(parameter WIDTH=32) (
        // META IN
        input rst,
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

    // internal wires
    wire den_neq;
    wire intern_rdy;
    // internal registers
    reg [WIDTH-1:0] temp_1;
    reg [WIDTH-1:0] temp_2;
    reg [WIDTH-1:0] temp_3;

    reg reg_rdy_1a;
    reg reg_rdy_1b;
    reg reg_rdy_2b;
    
    // wire assignments
    assign intern_rdy = reg_rdy_1a | reg_rdy_2b;
    assign rdy_out = intern_rdy;
    assign den_neq = |(l_den ^ r_den);
   
    // RESET Logic
    always @(posedge rst) begin
        reg_rdy_1a <= 1'b0;
        reg_rdy_1b <= 1'b0;
        reg_rdy_2b <= 1'b0;

        temp_1 <= 0;
        temp_2 <= 0;
        temp_3 <= 0;
    end

    always @(posedge clk) begin
        if (den_neg) begin
            // CLK 1
            temp_1 <= l_den * r_den;
            temp_2 <= r_num * l_den;
            temp_3 <= l_den * r_den;
            reg_rdy_1b <= 1'b1;

            // CLK 2
            s_num <= temp_1 + temp_2;
            s_den <= temp_3;
            reg_rdy_2b <= reg_rdy_1b;
        end
        else begin
            // CLK 1
            s_num <= l_num + r_num;
            s_den <= l_den;
            reg_rdy_1a <= 1'b1;
        end
    end

endmodule
