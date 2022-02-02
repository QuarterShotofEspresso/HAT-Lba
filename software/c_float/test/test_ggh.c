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

    // generate public key V
    struct matrix *V = new_matrix(size, size, range);
    gram_schmidt(V);
    struct matrix *VU = copy_matrix(V);
    struct matrix *VL = new_matrix(size, size, 1);
    lu_decomp(VU, VL);
    DATA_TYPE v_det = lu_det(VU);

    // generate unimodular/skew matrix U
    struct matrix *U = new_matrix(size, size, 1);
    unimodularize_matrix(U, 100, 5);

    // generate public key W
    struct matrix *W = new_matrix(size, size, 1);
    mxmar(W, V, U, 1);
    struct matrix *WU = copy_matrix(W);
    struct matrix *WL = new_matrix(size, size, 1);
    lu_decomp(WU, WL);
    DATA_TYPE w_det = lu_det(WU);

    // ensure both keys are non-singular
    while(!v_det || (v_det != v_det)) {
        // delete old key
        del_matrix(V);
        del_matrix(VL);
        del_matrix(VU);
        // construct new key
        V = gen_private_key(size, range, 0.7);
        VL = new_matrix(size, size, 1);
        VU = copy_matrix(V);
        lu_decomp(VU, VL);
        v_det = lu_det(VU);
    }

    while(!w_det || (w_det != w_det)) {
        // delete old key
        del_matrix(W);
        del_matrix(WL);
        del_matrix(WU);
        del_matrix(U);
        // construct new key
//        W = gen_public_key(V);
        U = new_matrix(size, size, 1);
        unimodularize_matrix(U, 100, 5);
        mxmar(W, V, U, 1);
        WU = copy_matrix(W);
        WL = new_matrix(size, size, 1);
        lu_decomp(WU, WL);
        w_det = lu_det(WU);
    }

    printf("V: ratio -- %f || det -- %f\n", hadamard(V, v_det), v_det);
    print_matrix(V);
    printf("W: ratio -- %f || det -- %f\n", hadamard(W, w_det), w_det);
    print_matrix(W);


    struct matrix *m = encode_msg(msg, strlen(msg), size);
    printf("Matrix-encoded message:\n");
    print_matrix(m);

    struct matrix *e = encrypt_msg(W, m, 1);
    printf("Encrypted matrix:\n");
    print_matrix(e);

    struct matrix *d = decrypt_msg(W, V, e);
    printf("Decrypted matrix: (should match matrix-encoded message)\n");
    print_matrix(d);

    char *decr_msg = decode_msg(d, strlen(msg), size);
    printf("Decoded message:\n");
    printf("%s\n", decr_msg);
    printf("Target message:\n");
    printf("%s\n", msg);

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
    del_matrix(e);
    del_matrix(d);
    free(decr_msg);


    return 0;
}