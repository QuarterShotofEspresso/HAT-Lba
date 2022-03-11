# Software

## Table of Contents
- [Directories](#directories)
- [Config.h](#config.h)
- [Matrix.h](#matrix.h)
- [How to Run](#how-to-run)

## Directories

- `builds` - contains the executables that are produced by `make`
- `c_fixed` - contains the fixed version of the lattice based functions and fpa functions
- `c_float` - contains the float version of the lattice based functions 
- `c_rational` - contains the rational version of the lattice based functions and rational helper functions 
- `output` - contains the logs of certain test results
- `prototype` - contains the python implementation of the lattice based functions 
- `src` - contains the ggh functions
- `test` - contains general tests among the different versions of lattice based functions

## Config.h

The config.h file contains macro definitions that help compile the different implementation versions.  

The first definition, `#define DATA_TYPE double`, assigns `DATA_TYPE` to the double type; when using the rational version, comment this out.  

Likewise, #define `DATA_TYPE struct rational` assigns `DATA_TYPE` to the rational struct type; when using the float or fixed version, comment this out.

Since the implementations use `DATA_TYPE` instead of a strict type (such as double or int), we can easily switch between implementations while testing by simply commenting one out.

The next two macros are used for the fixed-point implementation.  Changing `RATIONAL_WIDTH` changes the number of bits used for rounding; if a rounding error occurs, increase this.  
`INTEGER_WIDTH`, on the other hand, changes the number of bits that a value can be represented by; if an overflow error occurs, increase this.

The last three macros are simply representation selectors.  When using the fixed implementation, use `#define USE_FIXED_POINT`; for float implementation, use `#define USE_FLOATING_POINT`, and `#define USE_RATIONAL` for rational implementation.  Make sure only one is in use and comment out the rest.

## Matrix.h

The matrix.h file contains the primary interface for the lattice based function analysis.  The different versions (c_fixed, c_float, c_rational) found in the directory are different implementations of the same general functions, such as matrix creation and matrix calculations, and therefore share the same structs and definitions.  Each implementation includes this file and may contain additional header files specialized to each version in their respective directories.

## How to Run

### General Tests

To compile and run general tests in the software directory, first compile by doing:

#### `make test_name`

This will result in an executable file in the builds directory.  Then run with any appropriate arguments:

#### `./builds/test_name`

For example, `make test_decrypt` will build the application `test/test_decrypt.c`, and

#### `./builds/test_decrypt <size> <range> <message>`

will run the test.

### Version Specific Tests

To compile and run tests within the c_fixed, c_float and c_rational directories, concatenate the appropriate identifiers to the beginning of the test name.
For fixed (fix) point:

#### `make fix_test_name`

For floating (flt) point:

#### `make flt_test_name`

For rational (rat):

#### `make rat_test_name`

For example, to run test_dot.c with the fixed implementation, do:

#### `make fix_test_dot`

followed by

#### `./builds/fix_test_dot <col_size> <range>
