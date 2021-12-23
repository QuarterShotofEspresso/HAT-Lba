#include "fpa_matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    // parse command line args
    int col_size = atoi(argv[1]);
    int range = atoi(argv[2]);

    // declare and malloc vectors
    float *u = (float*)malloc(col_size * sizeof(float));
    float *v = (float*)malloc(col_size * sizeof(float));
    float *r = (float*)malloc(col_size * sizeof(float));

    // print and assign vectors
    for(int i = 0; i < col_size; ++i) {
        u[i] = rand() % range;
        v[i] = rand() % range;
        printf("u(%f)  v(%f), ", u[i], v[i]);
        printf("\n");
    }

    // write and print result
    fpa_project(u, v, r, col_size);

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
