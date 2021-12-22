#include "config.h"
#include "fixed_approximation.h"
#include "math.h"
#include <stdio.h>


static const int int_width = 20;
static const int rat_width = 20;

// using bit shifts
static DATA_TYPE upper_bound = 0.0;
static DATA_TYPE lower_bound = 0.0;


void init_fpa_meta() {

    printf("int_width: %d\nrat_width: %d\n", int_width, rat_width);
    
    upper_bound = pow(2, int_width - 1) - pow(2, -rat_width);
    lower_bound = -pow(2, int_width - 1);
    
    printf("upper_bound: %.10f\nlower_bound: %.10f\n", upper_bound, lower_bound);
    printf("resolution: %.10f\n", pow(2, -rat_width));

    return;
}


// deres function uses floating point trimmed to
DATA_TYPE mtfp(DATA_TYPE input) {

    DATA_TYPE interm = floor(input * pow(2, rat_width))/pow(2, rat_width);

    //printf("interm: %d\n", interm);

    if(interm < lower_bound) {
        interm = lower_bound;
        log_overflow(input, 1);
    } else if(interm > upper_bound) {
        interm = upper_bound;
        log_overflow(input, 0);
    }

    return interm;
}


void log_overflow(DATA_TYPE trigger, int lower_breached) {
    
    if(lower_breached) {
        fprintf(stderr, "ERR: Lower bound overflow: %f !< %f\n", trigger, lower_bound);
    } else {
        fprintf(stderr, "ERR: Upper bound overflow: %f !< %f\n", trigger, upper_bound);
    }

    return;
}


