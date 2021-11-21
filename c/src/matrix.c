// Authors: Ratnodeep Bandyopadhyay
// Copyright 11/20/21. All rights reserved.

#include "matrix.h"
#include "stdlib.h"
#include "qsoe_float_helper.h"


// READY FOR TESTING
struct matrix * new_matrix(int col_size, int row_size, int entry_range) {
    
    struct matrix *A = (struct matrix *)malloc(sizeof(struct matrix));
    A->row_size = row_size;
    A->col_size = col_size;


    if(entry_range == 1) {
        A->entry = (int*)calloc(row_size * col_size * sizeof(int));
    } else {
        // could run if large matrices are involved
        A->entry = (int*)malloc(row_size * col_size * sizeof(int));
        for(int i = 0; i < row_size; ++i) {
            for(int j = 0; j < col_size; ++j) {
                A->entry[i][j] = rand() % entry_range;
            }
        }
    }

    return A;
}



void del_matrix(struct matrix *A) {

    free(A->entry);
    free(A);

    return;
}



// READY FOR TESTING
int dot(struct matrix *u, struct matrix *v) {
    
    // catch: dim u != dim v
    if(u->col_size != v->col_size || u->row_size != col->size) {
        fprintf(stderr, "dot: dimension mismatch: u(%d, %d) v(%d, %d)\n", 
            u->col_size, u->row_size, v->col_size, v->row_size);
        return -1;
    }

    int dot_prod = 0;
    for(int i = 0; i < u->col_size; ++i) {
        dot_prod = dot_prod + (u->entry[0][i] * v->entry[0][i]);
    }

    return dot_prod;
}


//READY FOR TESTING
void gram_schmidt(struct matrix *A) {

    //int vary_shift = 0;

    for(int i = 0; i < dim; ++i) {
        for(int j = 0; j < dim; ++j) {
            
            //vary_shift = (rand() % vary) - (vary / 2); 
            for(int k = 0; k < dim; ++k) {
                A->entry[k][i] = A->entry[k][i] - project(A->entry[k][j], A->[k][i]);
            }
        
        }
    }

    return;
}


void babai(struct matrix *A, struct matrix *w, struct matrix *x) {

    lup_solve(A, w, x);
    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < A->col_size; ++j) { 
            x->[i][j] = round(x->entry[i][j]);
        }
    }

    return; 
}



