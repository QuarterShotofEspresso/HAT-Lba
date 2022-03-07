
// Internal
#include "../../config.h"
#include "../includes/fpa.h"

// External
#include <math.h>
#include <stdio.h>

// using bit shifts
static DATA_TYPE upper_bound = 0.0;
static DATA_TYPE lower_bound = 0.0;


// INIT_FPA_META: initialize the fixed-point approximation with the
// provided bit widths.
void init_fpa_meta() {

    printf("int_width: %d\nrat_width: %d\n", INTEGER_WIDTH, RATIONAL_WIDTH);
    
    upper_bound = pow(2, INTEGER_WIDTH - 1) - pow(2, -RATIONAL_WIDTH);
    lower_bound = -pow(2, INTEGER_WIDTH - 1);
    
    printf("upper_bound: %.10f\n", upper_bound);
    printf("lower_bound: %.10f\n", lower_bound);
    printf("resolution: %.10f\n", pow(2, -RATIONAL_WIDTH));

}


// MTFP: short for "map to fixed point" and maps the input to the
// closest representable number by the provided bit widths.
DATA_TYPE mtfp(DATA_TYPE input) {

    static int overflow_msg_counter = 0;

    DATA_TYPE approximation = floor(input * pow(2, RATIONAL_WIDTH))/pow(2, RATIONAL_WIDTH);

    // note: at most, print overflow message 20 times. (avoid flooding console/log files)
    if((overflow_msg_counter < 20) && (approximation < lower_bound || approximation > upper_bound)) {
        fprintf(stderr, "Overflow Warning: input %.10f with approximation %f cannot be represented with %d integer bits.\n",
                input, approximation, INTEGER_WIDTH);
        ++overflow_msg_counter;
    }

    return approximation;
}


