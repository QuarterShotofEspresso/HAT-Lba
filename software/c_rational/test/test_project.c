#include "../../matrix.h"
#include "../includes/rational.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(0);

    // parse command line args
    int col_size = atoi(argv[1]);
    int range = atoi(argv[2]);

    // declare and malloc vectors
    struct rational *u = (struct rational*)malloc(col_size * sizeof(struct rational));
    struct rational *v = (struct rational*)malloc(col_size * sizeof(struct rational));
    struct rational *r = (struct rational*)malloc(col_size * sizeof(struct rational));


    // print and assign vectors
    for(int i = 0; i < col_size; ++i) {
        u[i].num = 1 + rand() % range;
	u[i].den = 1;
        v[i].num = 1 + rand() % range;
	v[i].den = 1;
        printf("u(%d/%d)[%f]  v(%d/%d)[%f], ", u[i].num, u[i].den, (u[i].num / u[i].den), v[i].num, v[i].den, (v[i].num / v[i].den));
        printf("\n");
    }

    // write and print result
    project(u, v, r, col_size);

    // print result vector
    printf("\nproj_u(v) -> r:\n");
    for(int i = 0; i < col_size; ++i) {
        printf("r(%d/%d) ", r[i].num, r[i].den);
        printf("\n");
    }

    // deallocate memory
    free(u);
    free(v);
    free(r);

    return 0;
}
