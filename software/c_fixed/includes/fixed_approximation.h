#ifndef FIXED_APPROXIMATION_H
#define FIXED_APPROXIMATION_H


// print_fpa_meta
void init_fpa_meta();


// map_to_fixed_precision
//double map_to_fixed_precision(struct fixed_format *ff, double input);
double mtfp(double input);


// log_overflow
void log_overflow(double trigger, int lower_bound);


#endif // FIXED_APPROXIMATION_H
