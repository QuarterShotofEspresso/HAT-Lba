`timescale 1 ns/ 10 ps

module round_tb;
    
    // configuration integers
    parameter INTW=10;
    parameter RATW=10;
    integer BOUND=1000;
    integer TOTAL_TESTS = 20;
    integer DELAY = 3;

    reg [WIDTH-1:0] s_num;
    wire [WIDTH-1:0] s_den;

    round #(INTW, RATW) dut (clk, l_num, l_den, r_num, r_den, s_num, s_den);

    integer i;
    integer test_passed = 0;

    initial begin

        // TODO: Address plusarg > parameter generation!!

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
            test_vector = $urandom % BOUND;
            $display("Testing: "
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
