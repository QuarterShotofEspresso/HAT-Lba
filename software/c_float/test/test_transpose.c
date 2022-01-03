//
// Created by Ratnodeep Bandyopadhyay on 1/2/22.
//

#include "../includes/matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    int size = atoi(argv[1]);
    int range = atoi(argv[2]);

//    printf("Printed\n");

    struct matrix *A = new_matrix(size, size, range);
    struct matrix *AT = new_matrix(size, size, 1);

    transpose(AT, A);

//    printf("Printed\n");

    print_matrix(A);
    print_matrix(AT);

    del_matrix(A);
    del_matrix(AT);

    return 0;
}