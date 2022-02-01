//
// Created by Ratnodeep Bandyopadhyay on 1/3/22.
//

#include "../../matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "../../ggh.h"
#include <string.h>

#define ROW_SIZE m->row_size

// The purpose of this test is to verify that Ax = b and BAx = b
// produce identical results using mxmar, lu_solve, and lu_decomp.
int main(int argc, char *argv[]) {

    srand(time(NULL));
    int size = atoi(argv[1]);
    int range = atoi(argv[2]);
//    char *msg = argv[3];

    //NOTE:: A->entry[<->][v^]

    // test matrices
    struct matrix *V = gen_private_key(size, range, 0.7);
    struct matrix *U = new_matrix(size, size, 1);
    unimodularize_matrix(U, 5, 100);
    struct matrix *W = new_matrix(size, size, 1);
    mxmar(W, V, U, 1);

    // test vectors
    struct matrix *m = new_matrix(size, 1, 20000);

    struct matrix *e = new_matrix(size, 1, 1);
    struct matrix *VIe = new_matrix(size, 1, 1);
    struct matrix *Um = new_matrix(size, 1, 1);

    struct matrix *Wm = new_matrix(size, 1, 1);
    struct matrix *WIWm = new_matrix(size, 1, 1);


    // Initialize values
    struct matrix *VU = copy_matrix(V);
    struct matrix *VL = new_matrix(size, size, 1);
    lu_decomp(VU, VL);

    struct matrix *WU = copy_matrix(W);
    struct matrix *WL = new_matrix(size, size, 1);
    lu_decomp(WU, WL);


    // Multiply matrices
    mxmar(e, W, m, 3);
    mxmar(Um, U, m, 1);
    mxmar(Wm, W, m, 1);

    lu_solve(VL, VU, e->entry[0], VIe->entry[0]);
    lu_solve(WL, WU, Wm->entry[0], WIWm->entry[0]);

    printf("W:\n");
    print_matrix(W);

    printf("V:\n");
    print_matrix(V);

    // First Stage
    printf("Um:\n");
    print_matrix(Um);

    printf("VIe:\n");
    print_matrix(VIe);

    // Second Stage
    printf("m:\n");
    print_matrix(m);

    printf("WIWm:\n");
    print_matrix(WIWm);



    return 0;
}