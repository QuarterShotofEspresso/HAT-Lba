//
// Created by Ratnodeep Bandyopadhyay on 1/13/22.
//

#include "../../matrix.h"
#include "../../ggh.h"

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    int chunk_size = atoi(argv[1]);
    int entry_range = atoi(argv[2]);

    struct matrix *V = gen_private_key(chunk_size, entry_range, 0.7);
//    printf("Reached here: %p, col_size: %d, row_size: %d\n", &V, V->col_size, V->row_size);


    struct matrix *W = gen_public_key(V);

    printf("V:\n");
    print_matrix(V);
    printf("W:\n");
    print_matrix(W);

    del_matrix(V);
    del_matrix(W);

    return 0;
}