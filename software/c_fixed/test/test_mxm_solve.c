#include "../../matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "../includes/fpa.h"

// The purpose of this test is to verify that Ax = b and BAx = b
// // produce identical results using mxmar, lu_solve, and lu_decomp.

int main(int argc, char *argv[]) {

    srand(time(NULL));

    init_fpa_meta();

    int size = atoi(argv[1]);
    int range = atoi(argv[2]);

    struct matrix *A = new_matrix(size, size, range);
    struct matrix *AU = copy_matrix(A);
    struct matrix *AL = new_matrix(size, size, 1);
    struct matrix *x = new_matrix(size, 1, range);
    struct matrix *b = new_matrix(size, 1, 1);

    mxmar(b, A, x, 1);

    printf("vector generated: x:\n");
    print_matrix(x);

    lu_decomp(AU, AL);
    babai(AL, AU, b->entry[0], x->entry[0]);

    printf("vector resulted: x:\n");
    print_matrix(x);


    del_matrix(A);
    del_matrix(AU);
    del_matrix(AL);
    del_matrix(x);
    del_matrix(b);

    return 0;
}
