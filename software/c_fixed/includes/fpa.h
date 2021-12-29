#ifndef FIXED_APPROXIMATION_H
#define FIXED_APPROXIMATION_H

// General
#include "../../includes/config.h"

// print_fpa_meta
void init_fpa_meta();


// map_to_fixed_precision
//DATA_TYPE map_to_fixed_precision(struct fixed_format *ff, DATA_TYPE input);
DATA_TYPE mtfp(DATA_TYPE input);


// log_overflow
void log_overflow(DATA_TYPE trigger, int lower_bound);


#endif // FIXED_APPROXIMATION_H
