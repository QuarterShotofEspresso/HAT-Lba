`timescale 1 ns/ 10 ps



module round_tb;
    
    // configuration integers
    parameter INTW=10;
    parameter RATW=2;
    integer BOUND=1000;
    integer TOTAL_TESTS = 20;
    integer DELAY = 3;

    real pre_conv_fac = 2**(2*RATW);
    real post_conv_fac = 2**RATW;

    reg [INTW+(2*RATW)-1:0] in;
    wire [INTW+RATW-1:0] out;

    function [INTW+RATW-1:0] soft_round;
        input real in;
        begin
            soft_round = (in >= 0.5) ? $ceil(in) : $floor(in);
        end
    endfunction

    round #(INTW, RATW) dut (in, out);

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
            in = $urandom % BOUND;
            #DELAY;
            if (soft_round(in>>RATW) === out) begin
                $display("PASSED: ROUND(%.5f) = %.5f. Got: %.5f", in/pre_conv_fac, soft_round(in>>RATW)/post_conv_fac, out/post_conv_fac);
                $display("VALUE: %20b", in);
                $display("ROUND: %19b0", out);
            end
        end

        $display("%0d / %0d tests passed.\n", test_passed, TOTAL_TESTS);
        $finish;
    end


    //always begin
    //    #1 clk = ~clk;
    //end
    //initial begin
    //    clk = 0;
    //end


endmodule
