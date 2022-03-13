# Hardware
## Overview
This directory contains hardware modules that serve to accelerate computation speeds when using fixed-point
or rational representations.

## Table of Contents
- [Directories](#directories)
- [Running Sample Simulations](#Running Sample Simulations)

## Directories
- `hdl/` - contains the Verilog source code.  This is broken into two separate directories; one for rational and one for fixed point.
- `sim/` - contains test benches for each module in `hdl/`.
- `test/` - contains the compiled implementation of the test benches.

## Running Sample Simulations
`make <test_name> [PARGS=<plusargs>]` - deposits compiled simulation into `test/`. To test modules using the fixed-point
representation, use `make fix_test_round [PARGS=<plusargs>]`.
Plusargs serve as a method of customizing tests. The plusargs provided in these sample tests include:
 - `+TOTAL_TESTS`: controls the total number of tests to run. _(Default: 20)_
 - `+BOUND`: controls the upper bound of the random numbers generated. _(Default: 1000)_
 - `+DELAY`: varies the number of cycles given for the testing module to complete their task. _(Default: 3)_

###### Example Simulation Commands
`make test_add PARGS="+TOTAL_TESTS=500 +BOUND=50"`  
`make test_div`  
`make test_round PARGS="+DELAY=10"`