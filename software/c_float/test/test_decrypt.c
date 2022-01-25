//
// Created by Ratnodeep Bandyopadhyay on 1/3/22.
//

#include "../../matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

// The purpose of this test is to verify that Ax = b and BAx = b
// produce identical results using mxmar, lu_solve, and lu_decomp.
int main(int argc, char *argv[]) {

    srand(time(NULL));
    int size = atoi(argv[1]);
    int range = atoi(argv[2]);

    //NOTE:: A->entry[<->][v^]

    // allocate all matrix memory
    // Prepare Public Key V
    struct matrix *V = new_matrix(size, size, range);
    gram_schmidt(V);
    struct matrix *VU = copy_matrix(V);
    struct matrix *VL = new_matrix(size, size, 1);
    lu_decomp(VU, VL);
    DATA_TYPE V_det = lu_det(VU);
    printf("V: Ratio:%f\n", hadamard(V, V_det));
    print_matrix(V);

    // Prepare matrix U
    struct matrix *U = new_matrix(size, size, 1);
    unimodularize_matrix(U, 100, 5);

    // Prepare Public Key W
    struct matrix *W = new_matrix(size, size, 1);
    mxmar(W, V, U, 1);
    struct matrix *WU = copy_matrix(W);
    struct matrix *WL = new_matrix(size, size, 1);
    lu_decomp(WU, WL);
    DATA_TYPE W_det = lu_det(WU);
    printf("W: Ratio:%f\n", hadamard(W, W_det));
    print_matrix(W);

    // Test Vectors
//    DATA_TYPE *b = malloc(size * sizeof(DATA_TYPE));
//    DATA_TYPE *e = malloc(size * sizeof(DATA_TYPE));
//    DATA_TYPE *x = malloc(size * sizeof(DATA_TYPE));

    // Vectors using matrix constructor
    struct matrix *m  = new_matrix(size, 1, range);
    struct matrix *eV = new_matrix(size, 1, 1);
    struct matrix *eW = new_matrix(size, 1, 1);
    struct matrix *dV = new_matrix(size, 1, 1);
    struct matrix *dW = new_matrix(size, 1, 1);
    struct matrix *Vm = new_matrix(size, 1, 1);
    struct matrix *Wm = new_matrix(size, 1, 1);
    struct matrix *m_V = new_matrix(size, 1, 1);
    struct matrix *m_W = new_matrix(size, 1, 1);


    // Encryption of m with map W
    mxmar(eW, W, m, 1);
    mxmar(eV, V, m, 1);

    // Decryption starts
    babai(VL, VU, eW->entry[0], dW->entry[0]);
    babai(VL, VU, eV->entry[0], dV->entry[0]);

    mxmar(Wm, V, dW, 1);
    mxmar(Vm, V, dV, 1);

    lu_solve(WL, WU, Wm->entry[0], m_W->entry[0]);
    lu_solve(VL, VU, Vm->entry[0], m_V->entry[0]);



    // Babai's Output with public key and private key should be the same
//    printf("dV:\n");
//    print_matrix(dV);
//    printf("dW:\n");
//    print_matrix(dW);

//
//    // Eliminate V map
//    lu_solve(VL, VU, dV->entry[0], Vm->entry[0]);
//    lu_solve(VL, VU, dW->entry[0], Wm->entry[0]);
//
//
//    // Eliminate remaining key map
//    lu_solve(VL, VU, dV->entry[0], m_V->entry[0]);
//    lu_solve(WL, WU, dW->entry[0], m_W->entry[0]);
    // The resulting decoded information should be the same
    printf("True msg:\n");
    print_matrix(m);
    printf("Result from V enc msg:\n");
    print_matrix(m_V);
    printf("Result from W enc msg:\n");
    print_matrix(m_W);



    // Deallocate key memory
    del_matrix(V);
    del_matrix(VU);
    del_matrix(VL);
    del_matrix(U);
    del_matrix(W);
    del_matrix(WU);
    del_matrix(WL);
    // Deallocate vector memory
    del_matrix(m);
    del_matrix(eV);
    del_matrix(eW);
    del_matrix(dV);
    del_matrix(dW);
    del_matrix(Vm);
    del_matrix(Wm);


    return 0;
}