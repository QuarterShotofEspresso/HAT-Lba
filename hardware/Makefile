# Sample compilation
# iverilog -o test/test_mul.vvp sim/rat/test_mul.v hdl/rat/mul.v
# vvp test/test_mul.vvp

HDL_RAT_DIR = hdl/rat
SIM_RAT_DIR = sim/rat

test_%: $(HDL_RAT_DIR)/%.v $(SIM_RAT_DIR)/test_%.v
	iverilog -o test/$@.vvp $(SIM_RAT_DIR)/$@.v $<
	vvp test/$@.vvp $(PARGS)

round: hdl/fixed/round.v sim/fixed/test_round.v
	iverilog -o test/test_round.vvp sim/fixed/test_round.v $<
	vvp test/test_round.vvp $(PARGS)
