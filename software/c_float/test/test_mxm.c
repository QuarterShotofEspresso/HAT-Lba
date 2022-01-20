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
    int range = atoi(argv[2]);

    struct matrix *A_right = new_matrix(size, size, range);
    struct matrix *A_left = new_matrix(size, size, range);
    struct matrix *A_result = new_matrix(size, size, 1);

    mxm(A_result, A_left, A_right);

    print_matrix(A_left);
    print_matrix(A_right);
    printf("Results in:\n");
    print_matrix(A_result);

    del_matrix(A_right);
    del_matrix(A_left);
    del_matrix(A_result);

    return 0;
}