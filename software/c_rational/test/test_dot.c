#include "../../matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "../includes/rational.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    // parse command line args
    int col_size = atoi(argv[1]);
    int range = atoi(argv[2]);

    // declare and malloc vectors
    //float *u = (float*)malloc(col_size * sizeof(float));
    //float *v = (float*)malloc(col_size * sizeof(float));
    struct rational *u = (struct rational*)malloc(col_size * sizeof(float));
    struct rational *v = (struct rational*)malloc(col_size * sizeof(float));

    // print and assign vectors
    for(int i = 0; i < col_size; ++i) {
        u[i].num = 1 + rand() % range;
	u[i].den = 1 + rand() % range;
        v[i].num = 1 + rand() % range;
	v[i].den = 1 + rand() % range;
        printf("u(%d/%d)  v(%d/%d), ", u[i].num, u[i].den, v[i].num, v[i].den);
        printf("\n");
    }

    // write and print result
    struct rational prod = dot(u, v, col_size);
    printf("u.v = %d/%d\n", prod.num, prod.den);

    // deallocate memory
//    free(u);
//    free(v);

    return 0;
}
