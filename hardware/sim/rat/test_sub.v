`timescale 1 ns/ 10 ps

module add_tb;
    
    // configuration integers
    parameter WIDTH=32;
    integer BOUND=1000;
    integer TOTAL_TESTS = 20;
    integer DELAY = 4;

    reg [WIDTH-1:0] l_num;
    reg [WIDTH-1:0] l_den;
    reg [WIDTH-1:0] r_num;
    reg [WIDTH-1:0] r_den;
    wire [WIDTH-1:0] s_num;
    wire [WIDTH-1:0] s_den;
    wire rst;
    wire rdy;
    
    reg clk;

    add #(WIDTH) dut (clk, rst, l_num, l_den, r_num, r_den, s_num, s_den, rdy);

    integer i;
    integer test_passed = 0;

    initial begin

        // Add plusargs here if necessary
        if ($value$plusargs("BOUND=%0d", BOUND)) begin
            $display("Config param found. \'BOUND\' = %0d", BOUND);
        end
        if ($value$plusargs("TOTAL_TESTS=%0d", TOTAL_TESTS)) begin
            $display("Config param found. \'TOTAL_TESTS\' = %0d", TOTAL_TESTS);
        end
        if ($value$plusargs("DELAY=%0d", DELAY)) begin
            $display("Config param found. \'DELAY\' = %0d", DELAY);
        end

        test_passed = TOTAL_TESTS;

        for(i = 0; i < TOTAL_TESTS; ++i) begin
            l_num = $urandom % BOUND;
            l_den = $urandom % BOUND;
            r_num = $urandom % BOUND;
            r_den = $urandom % BOUND;
            #DELAY;
            if((l_num * r_den + l_den * r_num) !== s_num || l_den * r_den !== s_den) begin
                $display("TEST FAILED:\t(%0d / %0d) / (%0d / %0d) = (%0d / %0d) != (%0d / %0d)", l_num, l_den, r_num, r_den, l_num * r_den, l_den * r_num, s_num, s_den);
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
