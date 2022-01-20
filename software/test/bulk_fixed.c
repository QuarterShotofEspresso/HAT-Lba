//
// Created by Ratnodeep Bandyopadhyay on 12/25/21.
//

// General
#include "../config.h"
#include "../meta_matrix.h"

// Specialized
#include "../c_fixed/includes/fpa.h"
#include "../c_fixed/includes/fpa_matrix.h"
#include "../matrix.h"

// External
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main (int argc, char *argv[]) {

    // initialize metas for bulk test
    srand(time(NULL));
    init_fpa_meta();

    // parse args
    int iterations = atoi(argv[1]);
    int sub_iterations = atoi(argv[2]);
    int size = atoi(argv[3]);
    int range = atoi(argv[4]);

    // initialize matrix/vector variables
    struct matrix *U = NULL;
    struct matrix *L = NULL;
    struct matrix *fpa_U = NULL;
    struct matrix *fpa_L = NULL;

    DATA_TYPE *w = NULL;
    DATA_TYPE *x = NULL;
    DATA_TYPE *fpa_w = NULL;
    DATA_TYPE *fpa_x = NULL;

    // additional variables used in the for loop below
    DATA_TYPE hadamard_ratio = 0;
    DATA_TYPE determinant = 0;
    int test_counter = 0;
    int pass_counter = 0;

    // testing variables
    char test_passed;

    for(test_counter = 0; test_counter < iterations; ++test_counter) {

        printf("TEST %d -- ", test_counter);
        test_passed = 1;

        //while the determinant is 0 and ratio < 0.7, continue generating matrices.
        do {
            // create two new matrices A and L
            U = new_matrix(size, size, range);
            L = new_matrix(size, size, 1);

            // decompose matrices into U and A.
            lu_decomp(U, L);
            // compute determinant
            determinant = lu_det(U);
            // derive ratio
            hadamard_ratio = hadamard(U, determinant);

        } while(determinant == 0 || hadamard_ratio < 0.7);
        printf("ratio=%f -- ", hadamard_ratio);

        //copy matrices as fpa_U and fpa_L, these will be used with fpa functions
        fpa_U = copy_matrix(U);
        fpa_L = copy_matrix(L);

        //initialize vectors w, x and fpa complements: fpa_w, and fpa_x
        w = (DATA_TYPE *)malloc(size * sizeof(DATA_TYPE));
        x = (DATA_TYPE *)malloc(size * sizeof(DATA_TYPE));
        fpa_w = (DATA_TYPE *)malloc(size * sizeof(DATA_TYPE));
        fpa_x = (DATA_TYPE *)malloc(size * sizeof(DATA_TYPE));

        for(int i = 0; i < sub_iterations; ++i) {
            //initialize random values for both w and fpa_w vectors
            for (int j = 0; j < size; ++j) {
                fpa_w[j] = rand() % range;
                w[j] = fpa_w[j];
            }

            //call babai and fpa_babai
            babai(L, U, w, x);
            fpa_babai(fpa_L, fpa_U, fpa_w, fpa_x);

            //compare results: vec x and vec fpa_x
            for (int j = 0; j < size; ++j) {
                if (x[j] != fpa_x[j]) {
                    // if results mismatch fail test_passed
                    test_passed = 0;
                    break;
                } else if (j == size-1) {
                    pass_counter++;
                }
            }
        }

        if(test_passed) {
            printf("PASSED\n");
        } else {
            printf("FAILED\n");
        }
    }

    printf("TEST RESULT: %.2f%% (%d/%d) passed.\n", ((double)pass_counter/test_counter), pass_counter, test_counter * sub_iterations);

    // deallocate memory
    del_matrix(U);
    del_matrix(L);
    del_matrix(fpa_U);
    del_matrix(fpa_L);
    free(w);
    free(x);
    free(fpa_w);
    free(fpa_x);

    return 0;
}