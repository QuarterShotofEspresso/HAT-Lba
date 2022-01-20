//
// Created by Ratnodeep Bandyopadhyay on 1/3/22.
//

#include "../../matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    int size = atoi(argv[1]);
    int upper_range = atoi(argv[2]);
    int lower_range = atoi(argv[3]);

    struct matrix *A = new_matrix(size, size, 1);
    struct matrix *L = new_matrix(size, size, 1);

    unimodularize_matrix(A, upper_range, lower_range);

    printf("A:\n");
    print_matrix(A);

    lu_decomp(A, L);

    printf("U:\n");
    print_matrix(A);
    printf("L:\n");
    print_matrix(L);

    del_matrix(A);
    del_matrix(L);

    return 0;
}