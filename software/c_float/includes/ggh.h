//
// Created by Ratnodeep Bandyopadhyay on 1/2/22.
//

#ifndef LATTICE_GGH_H
#define LATTICE_GGH_H

#include "matrix.h"
#include "../../includes/config.h"


// GEN_PRIVATE_KEY: Given the size of the key and a
// pointer to the key, generate the private key V.
struct matrix * gen_private_key(int chunk_size, int entry_range, DATA_TYPE lower_hadamard_bound);


// GEN_PUBLIC_KEY: Given a private key V, generate
// the public key W by multiplying V by a unimodular matrix U.
// Mathematically, return W = UV.
struct matrix * gen_public_key(struct matrix *V);


// ENCODE_MSG: Encode a message of some arbitrary size
// into a matrix m. Divide the entire message of size msg_length
// into chunks of size chunk_size. Each chunk will be converted
// to an integer vector represented as the columns of matrix m.
void encode_msg(struct matrix *m, char *message, int msg_length, int chunk_size);


// DECODE_MSG: Decode a matrix containing a message m
// into a character message of size msg_length. The columns of
// matrix m should have column vectors of size chunk_size.
void decode_msg(char *message, struct matrix *m, int msg_length, int chunk_size);


// ENCRYPT_MSG: Encrypt the matrix-encoded message m using the public key
// W using the following formula. e = Wm + r. The vector r will be constructed
// with randomly selected numbers. Vector r should offset the message mapped by
// W by some small vector r.
void encrypt_msg(struct matrix *e, struct matrix *W, struct matrix *m, int r_bound);


// DECRYPT_MSG: Given the private key V and public key W, perform babai's algorithm
// on the encrypted message e, to find the closest lattice point to e, Wm. Then, solve
// for m by using an LU decomposition and LU linear solver.
void decrypt_msg(struct matrix *m, struct matrix *W, struct matrix *V, struct matrix *e);


#endif //LATTICE_GGH_H
