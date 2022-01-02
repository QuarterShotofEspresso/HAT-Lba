//
// Created by Ratnodeep Bandyopadhyay on 1/2/22.
//

#ifndef LATTICE_GGH_H
#define LATTICE_GGH_H

#include "matrix.h"
#include "../../includes/config.h"


// GEN_PRIVATE_KEY:
void gen_private_key(struct matrix *private_key, int size);


// GEN_PUBLIC_KEY:
void gen_public_key(struct matrix *public_key);


// ENCODE_MSG
void encode_msg(DATA_TYPE *m, char *message, int size);


// DECODE_MSG
void decode_msg(char *message, DATA_TYPE *m, int size);


// ENCRYPT_MSG
void encrypt_msg(DATA_TYPE *e, struct matrix *public_key, DATA_TYPE *m);


// DECRYPT_MSG
void decrypt_msg(DATA_TYPE *m, struct matrix *public_key, struct matrix *private_key, DATA_TYPE *e);


#endif //LATTICE_GGH_H
