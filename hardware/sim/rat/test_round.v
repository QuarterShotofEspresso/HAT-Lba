`timescale 1 ns/ 10 ps

module round_tb;
    
    // configuration integers
    parameter WIDTH=32;
    integer BOUND=1000;
    integer TOTAL_TESTS = 20;
    integer DELAY = 4;

    reg [WIDTH-1:0] in_num;
    reg [WIDTH-1:0] in_den;
    wire [WIDTH-1:0] out_num;
    wire [WIDTH-1:0] out_den;
    reg [WIDTH-1:0] expect;
    reg rst;
    wire rdy;
    
    reg clk;

    round #(WIDTH) dut (clk, rst, in_num, in_den, out_num, out_den, rdy);

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

        test_passed = 0;

        for(i = 0; i < TOTAL_TESTS; ++i) begin
            in_num = $urandom % BOUND;
            in_den = $urandom % BOUND;
            #DELAY;
            expect = ((in_num / in_den) + ((in_num % in_den) >= (in_den / 2)));
            #DELAY
            if(expect === out_num) begin
                $display("TEST PASSED:\t(%0d / %0d)[%0.3f] == %0d === %0d", in_num, in_den, ((in_num + 0.0)/in_den), expect, out_num);
                test_passed++;
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
