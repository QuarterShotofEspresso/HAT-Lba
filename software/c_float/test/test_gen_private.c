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

    struct matrix *V = NULL;

    printf("Reached here\n");
    gen_private_key(V, chunk_size, entry_range, 0.7);
    printf("Reached here: %p\n", V);

    print_matrix(V);
    printf("Reached here\n");


    del_matrix(V);

    return 0;
}