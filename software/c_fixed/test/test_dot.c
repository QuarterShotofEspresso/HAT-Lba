#include "fpa_matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "fpa.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    init_fpa_meta();

    // parse command line args
    int col_size = atoi(argv[1]);
    int range = atoi(argv[2]);

    // declare and malloc vectors
    DATA_TYPE *u = (DATA_TYPE*)malloc(col_size * sizeof(DATA_TYPE));
    DATA_TYPE *v = (DATA_TYPE*)malloc(col_size * sizeof(DATA_TYPE));

    // print and assign vectors
    for(int i = 0; i < col_size; ++i) {
        u[i] = mtfp(rand() % range);
        v[i] = mtfp(rand() % range);
        printf("u(%f)  v(%f), ", u[i], v[i]);
        printf("\n");
    }

    // write and print result
    DATA_TYPE prod = fpa_dot(u, v, col_size);
    printf("u.v = %f\n", prod);

    // deallocate memory
    free(u);
    free(v);

    return 0;
}
