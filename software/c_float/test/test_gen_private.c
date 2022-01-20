//
// Created by Ratnodeep Bandyopadhyay on 1/7/22.
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

    print_matrix(V);

    del_matrix(V);

    return 0;
}