// Created by Ratnodeep Bandyopadhyay on 1/3/22
#include "../../matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "../includes/fpa.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    init_fpa_meta();

    int size = atoi(argv[1]);
    int size_odd = atoi(argv[2]);
    int range = atoi(argv[3]);

    struct matrix *A_right = new_matrix(size, size_odd, range);
    struct matrix *A_left = new_matrix(size, size, range);
    struct matrix *A_result = new_matrix(size, size_odd, 1);

    mxmar(A_result, A_left, A_right, 1);

    print_matrix(A_left);
    print_matrix(A_right);
    printf("Results in:\n");
    print_matrix(A_result);

    del_matrix(A_right);
    del_matrix(A_left);
    del_matrix(A_result);

    return 0;
}
