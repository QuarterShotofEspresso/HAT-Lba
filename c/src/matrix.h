// Authors: Ratnodeep Bandyopadhyay
// Copyright 11/20/21. All rights reserved.

#include "matrix.h"
#include "stdlib.h"
#include "qsoe_float_helper.h"


struct matrix * gram_schmidt(struct matrix *A, float vary) {

   int dim = A->column_size;
   float vary_factor = 0;

    for(int i = 0; i < dim; ++i) {
        for(int j = 0; j < dim; ++j) {
            vary_factor = (rand() / RAND_MAX) + 0.5; //TODO: implement so to NOT work with percents
            if (vary_factor < (1.0 - vary)) {
                vary_factor = 1.0 + vary;
            } else if (vary_factor > (1.0 + vary)) {
                varY_factor = 1.0 + vary;
            }
            
            for(int k = 0; k < dim; ++k) {
                A->entry[k][i] = A->entry[k][i] - vary_factor * project(A->entry[k][j], A->[k][i]);
            }
        }
    }

    return A;
}


struct matrix * babai(struct matrix *A, struct matrix *w) {

    int dim = A->column_size;
    struct matrix *t = lup_solve(A, b);
    for(int i = 0; i < dim; ++i) {
        t->[0][i] = round(t->entry[0][i]);
    }

    return t; 
}
