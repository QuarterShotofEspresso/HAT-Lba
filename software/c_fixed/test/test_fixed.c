#include "fixed_approximation.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char *argv[]) {

    int interval = atoi(argv[2]);
    int end_at = atoi(argv[1]) * interval;

    double t = 0.0;
    double inc_by = 1.0/interval;

    init_fpa_meta();

    for(int i = 0; i < end_at; ++i) {
        printf("t: %.10f -> %.10f\n", t, mtfp(t));
        t += inc_by;
    }

    return 0;
}
