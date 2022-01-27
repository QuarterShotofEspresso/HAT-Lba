//
// Created by Ratnodeep Bandyopadhyay and Serena Lew on 1/3/22.
//

#include "../../matrix.h"
#include "../../ggh.h"

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    // cmdline parameters
    char* msg = argv[1];
    int chunk_size = atoi(argv[2]);
    int entry_range = atoi(argv[3]);

    // other parameters and variables
    int r_bound = 3;
    int msg_length = strlen(msg);

    // Initialize private and public key
    struct matrix *V = gen_private_key(chunk_size, entry_range, 0.7);
    struct matrix *W = gen_public_key(V);
    printf("Done generating keys\n");

    // encode message
    struct matrix *m = encode_msg(msg, msg_length, chunk_size);
    printf("Done encoding msgs\n");

    // encrypt original messages
    struct matrix *e = encrypt_msg(W, m, r_bound);
    printf("Done encrypting msgs\n");

    // decrypt encrypted messages
    struct matrix *d = decrypt_msg(W, V, e);
    printf("Done decrypting msgs\n");

    // decode decrypted messages
    char *msg_res = decode_msg(d, msg_length, chunk_size);
    printf("Done decoding msgs\n");


    printf("Generated private key \n");
    print_matrix(V);
    printf("Generated public key \n");
    print_matrix(W);
    printf("\n");

    printf("========================\n");
    printf("Message encoded as matrix:\n");
    print_matrix(m);

    printf("========================\n");
    printf("Message encrypted:\n");
    print_matrix(e);

    printf("========================\n");
    printf("Message decrypted:\n");
    print_matrix(d);

    printf("========================\n");
    printf("Message to encrypt:\n%s\n\n", msg);
    printf("Decryption result:\n%s\n", msg_res);

    del_matrix(V);
    del_matrix(W);
    del_matrix(m);
    del_matrix(e);
    del_matrix(d);
    free(msg_res);

    return 0;
}
