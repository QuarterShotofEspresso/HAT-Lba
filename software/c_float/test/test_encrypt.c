// Serena Lew

#include "../../matrix.h"
#include "../../ggh.h"

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    char* msg_en = argv[1];
    int chunk_size = atoi(argv[2]);
    int entry_range = atoi(argv[3]);	// some number between 300 and 2000
    //int r_bound = atoi(argv[4]);	// 0.1 * entry_range
    int r_bound = entry_range * 0.1;

    // Generate private and public key
    printf("Generating private key \n");
    struct matrix *V = gen_private_key(chunk_size, entry_range, 0.7);
    print_matrix(V);
    printf("Generating public key \n");
    struct matrix *W = gen_public_key(V);
    print_matrix(W);
    printf("\n");

    // encode message
    int msg_size = strlen(msg_en);

    struct matrix *m = encode_msg(msg_en, msg_size, chunk_size);
    printf("Message to encode: \n%s\n\n", msg_en);
    printf("Matrix of encoded message: \n");
    print_matrix(m);
    //printf("%f\n", m->entry[0][0]);

    printf("\n");

    // encrypt message
    struct matrix *e = encrypt_msg(W, m, 1);
    struct matrix *e2 = encrypt_msg(W, m, 1);
    printf("Encrypted matrix of encoded matrix: \n");
    print_matrix(e);
    printf("Test Encrypted: \n");
    print_matrix(e);


    // decrypt message
    struct matrix *m2 = decrypt_msg(W, V, e);
    printf("Decrypted matrix of encrypted matrix: \n");
    print_matrix(m2);

    char* msg_dc = decode_msg(m2, msg_size, chunk_size);
    printf("Message from decoded matrix: \n%s\n", msg_dc);

    del_matrix(V);
    del_matrix(W);
    del_matrix(m);
    del_matrix(e);
    del_matrix(m2);

    return 0;
}
