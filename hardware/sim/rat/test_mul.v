`timescale 1 ns/ 10 ps
//`include "hdl/rat/mul.v"


module mul_tb;
    
    parameter WIDTH=32;
    parameter BOUND=1000;
    parameter TOTAL_TESTS = 20;

    reg [WIDTH-1:0] l_num;
    reg [WIDTH-1:0] l_den;
    reg [WIDTH-1:0] r_num;
    reg [WIDTH-1:0] r_den;
    wire [WIDTH-1:0] s_num;
    wire [WIDTH-1:0] s_den;

    reg clk;

    mul #(WIDTH) dut (clk, l_num, l_den, r_num, r_den, s_num, s_den);

    integer i;
    integer test_passed = TOTAL_TESTS;

    initial begin
        
        for(i = 0; i < TOTAL_TESTS; ++i) begin
            l_num = $urandom % BOUND;
            l_den = $urandom % BOUND;
            r_num = $urandom % BOUND;
            r_den = $urandom % BOUND;
            #3;
            if(l_num * r_num !== s_num || l_den * r_den !== s_den) begin
                $display("TEST FAILED:\t(%0d / %0d) * (%0d / %0d) = (%0d / %0d) != (%0d / %0d)", l_num, l_den, r_num, r_den, l_num * r_num, l_den * r_den, s_num, s_den);
                test_passed--;
            end
        end

        $display("%0d / %0d tests passed.\n", test_passed, TOTAL_TESTS);
        $finish;
    end


    always begin
        #1 clk = ~clk;
    end
    initial begin
        clk = 0;
    end


endmodule
