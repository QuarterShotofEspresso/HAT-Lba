#include "../../matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "../includes/fpa.h"

int main(int argc, char *argv[]) {

    srand(0);
    
    init_fpa_meta();

    // parse command line args
    int col_size = atoi(argv[1]);
    int range = atoi(argv[2]);

    // declare and malloc vectors
    DATA_TYPE *u = (DATA_TYPE*)malloc(col_size * sizeof(DATA_TYPE));
    DATA_TYPE *v = (DATA_TYPE*)malloc(col_size * sizeof(DATA_TYPE));
    DATA_TYPE *r = (DATA_TYPE*)malloc(col_size * sizeof(DATA_TYPE));

    // print and assign vectors
    for(int i = 0; i < col_size; ++i) {
        u[i] = mtfp(rand() % range);
        v[i] = mtfp(rand() % range);
        printf("u(%f)  v(%f), ", u[i], v[i]);
        printf("\n");
    }

    // write and print result
    project(u, v, r, col_size);

    // print result vector
    printf("\nproj_u(v) -> r:\n");
    for(int i = 0; i < col_size; ++i) {
        printf("r(%f) ", r[i]);
        printf("\n");
    }

    // deallocate memory
    free(u);
    free(v);
    free(r);

    return 0;
}
