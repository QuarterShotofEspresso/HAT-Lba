//
// Created by Ratnodeep Bandyopadhyay on 1/7/22.
//

#include "../includes/matrix.h"
#include "../includes/ggh.h"

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    int chunk_size = atoi(argv[1]);
    int entry_range = atoi(argv[2]);

    struct matrix *V = gen_private_key(chunk_size, entry_range, 0.7);
    printf("Reached here: %p, col_size: %d, row_size: %d\n", &V, V->col_size, V->row_size);

    print_matrix(V);
    printf("Reached here: %p\n", V);

    del_matrix(V);

    return 0;
}