//
// Created by Ratnodeep Bandyopadhyay on 1/3/22.
//

#include "../includes/matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    int size = atoi(argv[1]);
    int range = atoi(argv[2]);

    struct matrix *A = new_matrix(size, size, range);
    struct matrix *r = new_matrix(size, 1, 1);
    struct matrix *v = new_matrix(size, 1, range);

    mxv(r->entry[0], A, v->entry[0]);

    print_matrix(A);
    print_matrix(v);
    printf("Results in:\n");
    print_matrix(r);

    del_matrix(A);
    del_matrix(r);
    del_matrix(v);

    return 0;
}