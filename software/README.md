# Software

## Table of Contents
- [Directories](#directories)
- [Config.h](#configh)
- [Matrix.h](#matrixh)
- [How to Run](#how-to-run)

## Directories

- `builds` - contains the executables that are produced by `make`
- `c_fixed` - contains the fixed implementation of the lattice based functions and fpa functions
- `c_float` - contains the float implementation of the lattice based functions 
- `c_rational` - contains the rational implementation of the lattice based functions and rational helper functions 
- `output` - contains the logs of certain test results
- `prototype` - contains the python implementation of the lattice based functions 
- `src` - contains the ggh functions
- `test` - contains general tests among the different implementations of lattice based functions

## Config.h

The config.h file contains macro definitions that help compile the different implementations.  

The first few macros assign `DATA_TYPE` to the appropriate data type:
- `#define DATA_TYPE double` assigns `DATA_TYPE` to the double type; when using the rational implementation, comment this out.  
- `#define DATA_TYPE struct rational` assigns `DATA_TYPE` to the rational struct type; when using the float or fixed implementation, comment this out.

Since the implementations use `DATA_TYPE` instead of a specific type (such as double or int), we can easily switch between the different implementations while testing by simply commenting one out.

The next two macros, `RATIONAL_WIDTH` and `INTEGER_WIDTH`, are used for the fixed-point implementation.
- `RATIONAL_WIDTH` changes the number of bits used for rounding; if a rounding error occurs, increase this.  
- `INTEGER_WIDTH`, on the other hand, changes the number of bits that a value can be represented by; if an overflow error occurs, increase this.

The last three macros are simply representation selectors.  Make sure only one is in use and comment out the rest.
- use `#define USE_FIXED_POINT` for fixed implementation
- use `#define USE_FLOATING_POINT` for float implementation
- use `#define USE_RATIONAL` for rational implementation.  

## Matrix.h

The matrix.h file contains the primary interface for the lattice based function analysis.  The different implementations (`c_fixed`, `c_float`, and `c_rational`) found in the directory are based on the same primary functions.  

For example, functions such as `new_matrix`, `print_matrix`, and `project` are used by all three implementations.  Though they may slightly different code due to their respective datatype, they share the same structs and definitions.  

Each implementation includes matrix.h and may contain additional header files specialized to each implementation in their respective directories.

## How to Run


### General Tests

To compile and run general tests in the software directory, first do:

#### `make test_name`

This will result in an executable file in the builds directory.  Then run with the appropriate arguments:

#### `./builds/test_name arg1 arg2 ..`

For example, `make test_decrypt` will build the application `test/test_decrypt.c`, and

#### `./builds/test_decrypt <size> <range> <message>`

will run the test.


### Version Specific Tests

To compile and run tests within the `c_fixed`, `c_float` and `c_rational directories`, concatenate the appropriate identifiers to the beginning of the test name.
- For fixed (fix) point: `make fix_test_name`
- For floating (flt) point: `make flt_test_name`
- For rational (rat): `make rat_test_name`

For example, to run test_dot.c with the fixed implementation, do:

#### `make fix_test_dot`

followed by

#### `./builds/fix_test_dot <col_size> <range>`
