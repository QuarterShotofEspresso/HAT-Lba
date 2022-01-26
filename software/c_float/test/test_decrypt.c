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
    char *msg = argv[3];

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



    struct matrix *m = encode_msg(msg, strlen(msg), size);
//    struct matrix *m  = new_matrix(size, ROW_SIZE, range);
//    struct matrix *eV = new_matrix(size, ROW_SIZE, 1);
//    struct matrix *eW = new_matrix(size, ROW_SIZE, 1);
//    struct matrix *dV = new_matrix(size, ROW_SIZE, 1);
//    struct matrix *dW = new_matrix(size, ROW_SIZE, 1);
//    struct matrix *Vm = new_matrix(size, ROW_SIZE, 1);
//    struct matrix *Wm = new_matrix(size, ROW_SIZE, 1);
//    struct matrix *m_V = new_matrix(size, ROW_SIZE, 1);
//    struct matrix *m_W = new_matrix(size, ROW_SIZE, 1);

    struct matrix *eW2 = new_matrix(size, ROW_SIZE, 1);
    struct matrix *dW2 = new_matrix(size, ROW_SIZE, 1);



    // Encryption of m with map W
//    mxmar(eW, W, m, 1);
//    mxmar(eV, V, m, 1);
    eW2 = encrypt_msg(W, m, 1);

    // Decryption starts
//    for(int i = 0; i < ROW_SIZE; ++i) {
//        babai(VL, VU, eW->entry[i], dW->entry[i]);
//        babai(VL, VU, eV->entry[i], dV->entry[i]);
//    }
//
//    mxmar(Wm, V, dW, 1);
//    mxmar(Vm, V, dV, 1);
//
//    for(int i = 0; i < ROW_SIZE; ++i) {
//        babai(WL, WU, Wm->entry[i], m_W->entry[i]);
//        babai(VL, VU, Vm->entry[i], m_V->entry[i]);
//    }

    dW2 = decrypt_msg(W, V, eW2);



    printf("True msg:\n");
    print_matrix(m);
//    printf("Result from V enc msg:\n");
//    print_matrix(m_V);
//    printf("Result from W enc msg:\n");
//    print_matrix(m_W);
    printf("Reuslt from decrypt:\n");
    print_matrix(dW2);


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
//    del_matrix(eV);
//    del_matrix(eW);
//    del_matrix(dV);
//    del_matrix(dW);
//    del_matrix(Vm);
//    del_matrix(Wm);


    return 0;
}