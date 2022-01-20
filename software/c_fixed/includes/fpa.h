#ifndef FIXED_APPROXIMATION_H
#define FIXED_APPROXIMATION_H



#include "../../config.h"

// INIT_FPA_META: initialize the fixed-point approximation with the
// provided bit widths.
void init_fpa_meta();


// MTFP: short for "map to fixed point" and maps the input to the
// closest representable number by the provided bit widths.
DATA_TYPE mtfp(DATA_TYPE input);



#endif // FIXED_APPROXIMATION_H
