//
// Created by Ratnodeep Bandyopadhyay on 1/2/22.
//

#include "../includes/ggh.h"
#include "../includes/matrix.h"

#include <stdio.h>
#include <stdlib.h>


// GEN_PRIVATE_KEY: Given the size of the key and a
// pointer to the key, generate the private key V.
struct matrix * gen_private_key(int chunk_size, int entry_range, DATA_TYPE lower_hadamard_bound) {

    struct matrix *V = new_matrix(chunk_size, chunk_size, entry_range);
    struct matrix *VL = new_matrix(chunk_size, chunk_size, 1);
    struct matrix *VU = copy_matrix(V);

    gram_schmidt(V);

    lu_decomp(VU, VL);

    DATA_TYPE V_det = lu_det(VU);
    DATA_TYPE ratio = hadamard(V, V_det);

    if(ratio < lower_hadamard_bound) {
        fprintf(stderr, "error: geometry of private key is insufficient.\n");
    }

    del_matrix(VL);
    del_matrix(VU);

    return V;
}


// GEN_PUBLIC_KEY: Given a private key V, generate
// the public key W by multiplying V by a unimodular matrix U.
// Mathematically, return W = UV.
struct matrix * gen_public_key(struct matrix *V) {

    struct matrix *W = new_matrix(V->col_size, V->row_size, 1);
    struct matrix *U = new_matrix(V->col_size, V->row_size, 1);

    unimodularize_matrix(U, 100, 5);
    mxm(W, U, V);

    del_matrix(U);

    return W;
}


// ENCODE_MSG: Encode a message of some arbitrary size
// into a matrix m. Divide the entire message of size msg_length
// into chunks of size chunk_size. Each chunk will be converted
// to an integer vector represented as the columns of matrix m.
void encode_msg(struct matrix *m, char *message, int msg_length, int chunk_size) {

    int total_chunks = (msg_length / chunk_size) + 1; // row_size (total columns)

    if(m == NULL) {
        m = new_matrix(chunk_size, total_chunks, 1);
    }

    for(int i = 0; i < msg_length; ++i) {
        m->entry[i / chunk_size][i % chunk_size] = (int)message[i];
    }
}


// DECODE_MSG: Decode a matrix containing a message m
// into a character message of size msg_length. The columns of
// matrix m should have column vectors of size chunk_size.
void decode_msg(char *message, struct matrix *m, int msg_length, int chunk_size) {

    for(int i = 0; i < msg_length; ++i) {
        message[i] = (char)(m->entry[i / chunk_size][i % chunk_size]);
    }
}


// ENCRYPT_MSG: Encrypt the matrix-encoded message m using the public key
// W using the following formula. e = Wm + r. The vector r will be constructed
// with randomly selected numbers. Vector r should offset the message mapped by
// W by some small vector r.
void encrypt_msg(struct matrix *e, struct matrix *W, struct matrix *m, int r_bound) {

    // encrypt each encoded message vector via the linear map W
    for(int i = 0; i < m->row_size; ++i) {
//        mxv(e->entry[i], W, m->entry[i]);
        mxm(e, W, m);
    }

    // double the bound
    int double_r_bound = 2 * r_bound;

    // slightly randomize the encoded message e
    for(int i = 0; i < m->row_size; ++i) {
        for(int j = 0; j < m->col_size; ++j) {
            e->entry += (rand() % double_r_bound) - r_bound;
        }
    }
}


// DECRYPT_MSG: Given the private key V and public key W, perform babai's algorithm
// on the encrypted message e, to find the closest lattice point to e, Wm. Then, solve
// for m by using an LU decomposition and LU linear solver.
void decrypt_msg(struct matrix *m, struct matrix *W, struct matrix *V, struct matrix *e) {

    // lu-decompose the private key
    struct matrix *VU = copy_matrix(V);
    struct matrix *VL = new_matrix(V->col_size, V->row_size, 1);
    lu_decomp(VU, VL);

    struct matrix *WU = copy_matrix(W);
    struct matrix *WL = new_matrix(W->col_size, W->row_size, 1);
    lu_decomp(WU, WL);

    struct matrix *Wm = new_matrix(m->col_size, 1, 1);

    // run babai's algorithm with encoded message e
    for(int i = 0; i < m->row_size; ++i) {
        babai(VL, VU, e->entry[i], Wm->entry[i]);
        lu_solve(WL, WU, Wm->entry[i], m->entry[i]);
    }

    del_matrix(VU);
    del_matrix(VL);
    del_matrix(WU);
    del_matrix(WL);
    del_matrix(Wm);

    return;
}

