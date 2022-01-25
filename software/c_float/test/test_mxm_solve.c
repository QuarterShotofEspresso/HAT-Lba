//
// Created by Ratnodeep Bandyopadhyay on 1/3/22.
//

#include "../../matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

// The purpose of this test is to verify that Ax = b and BAx = b
// produce identical results using mxmar, lu_solve, and lu_decomp.
int main(int argc, char *argv[]) {

    srand(time(NULL));
    int size = atoi(argv[1]);
    int range = atoi(argv[2]);

    struct matrix *A = new_matrix(size, size, range);
    struct matrix *AU = copy_matrix(A);
    struct matrix *AL = new_matrix(size, size, 1);
    struct matrix *x = new_matrix(size, 1, range);
    struct matrix *b = new_matrix(size, 1, 1);

    mxmar(b, A, x, 1);

    printf("vector generated: x:\n");
    print_matrix(x);

    lu_decomp(AU, AL);
    babai(AL, AU, b->entry[0], x->entry[0]);

    printf("vector resulted: x:\n");
    print_matrix(x);


    del_matrix(A);
    del_matrix(AU);
    del_matrix(AL);
    del_matrix(x);
    del_matrix(b);



    //NOTE:: A->entry[<->][v^]

    // allocate all matrix memory
    // Matrix A
//    struct matrix *A = new_matrix(size, size, range);
//    struct matrix *AU = copy_matrix(A);
//    struct matrix *AL = new_matrix(size, size, 1);
//    // Matrix B
//    struct matrix *B = new_matrix(size, size, range);
//    // Matrix C
//    struct matrix *C = new_matrix(size, size, 1);
//    struct matrix *CU;
//    struct matrix *CL = new_matrix(size, size, 1);
//    // Vectors
//    DATA_TYPE *b = malloc(size * sizeof(DATA_TYPE));
//    DATA_TYPE *x = malloc(size * sizeof(DATA_TYPE));
//
//    // populate b with data
//    for(int i = 0; i < size; ++i) b[i] = i;
//
//    // setup B
//    printf("Left:\n");
//    print_matrix(B);
//    // Set up AU and AL
//    lu_decomp(AU, AL);
//    printf("Right:\n");
//    print_matrix(A);
//
//    // Calculate C and setup CU and CL
//    mxmar(C, B, A, 1);
//    CU = copy_matrix(C);
//    lu_decomp(CU, CL);
//    printf("Results in:\n");
//    print_matrix(C);
//
//    // perform an LU solve with both forms
//    lu_solve(AL, AU, b, x);
//    for(int i = 0; i < size; ++i) printf("x[%d]=%f\n", i, x[i]); // print the results of lu_solve
//    printf("\n");
//    lu_solve(CL, CU, b, x);
//    for(int i = 0; i < size; ++i) printf("x[%d]=%f\n", i, x[i]); // print the results of lu_solve
//    printf("\n");
//
//
//
//    // Deallocate all memory
//    del_matrix(A);
//    del_matrix(AU);
//    del_matrix(AL);
//    del_matrix(B);
//    del_matrix(C);
//    del_matrix(CU);
//    del_matrix(CL);
//    free(b);
//    free(x);




    return 0;
}