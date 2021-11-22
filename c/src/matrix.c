// Authors: Ratnodeep Bandyopadhyay
// Copyright 11/20/21. All rights reserved.

#include "matrix.h"
#include "stdlib.h"
#include "stdio.h"
//#include "qsoe_float_helper.h"


// READY FOR TESTING
struct matrix * new_matrix(int col_size, int row_size, int entry_range) {
    
    struct matrix *A = (struct matrix *)malloc(sizeof(struct matrix));
    A->row_size = row_size;
    A->col_size = col_size;
    A->entry = (int**)malloc(row_size * sizeof(int*));

    if(entry_range == 1) {
		for(int i = 0; i < A->row_size; ++i) {
			A->entry[i] = (int*)calloc(col_size, sizeof(int));
		}
    }

    else {
        for(int i = 0; i < A->row_size; ++i) {
            A->entry[i] = (int*)malloc(col_size * sizeof(int));
            for(int j = 0; j < col_size; ++j) {
                A->entry[i][j] = rand() % entry_range;
            }
        }
    }

    return A;
}



void del_matrix(struct matrix *A) {

    for(int i = 0; i < A->row_size; ++i)
        free(A->entry[i]);
    free(A->entry);
    free(A);

    return;
}



// READY FOR TESTING
int dot(struct matrix *u, struct matrix *v) {
    
    int dot_prod = 0;
    for(int i = 0; i < u->col_size; ++i) {
        dot_prod = dot_prod + (u->entry[0][i] * v->entry[0][i]);
    }

    return dot_prod;
}


//READY FOR TESTING
void gram_schmidt(struct matrix *A) {

    //for(int i = 0; i < dim; ++i) {
    //    for(int j = 0; j < dim; ++j) {
    //        //vary_shift = (rand() % vary) - (vary / 2); 
    //        for(int k = 0; k < A->col_size; ++k) {
    //            A->entry[k][i] = A->entry[k][i] - project(A->entry[k][j], A->[k][i]);
    //        }
    //    }
    //}

    //return;
}


void lup_solve(struct matrix *A, struct matrix *b, struct matrix *x) { }


void babai(struct matrix *A, struct matrix *w, struct matrix *x) {

    lup_solve(A, w, x);
    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < A->col_size; ++j) { 
            //x->entry[i][j] = qsoe_round(x->entry[i][j]);
            x->entry[i][j] = x->entry[i][j];
        }
    }

    return; 
}



