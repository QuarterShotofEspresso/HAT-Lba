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

    // print and assign vectors
    for(int i = 0; i < col_size; ++i) {
        u[i] = rand() % range;
        v[i] = rand() % range;
        printf("u(%f)  v(%f), ", u[i], v[i]);
        printf("\n");
    }

    // write and print result
    float prod = fpa_dot(u, v, col_size);
    printf("u.v = %f\n", prod);

    // deallocate memory
    free(u);
    free(v);

    return 0;
}
