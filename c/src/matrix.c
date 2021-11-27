// Authors: Ratnodeep Bandyopadhyay
// Copyright 11/20/21. All rights reserved.

#include "matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
//#include "qsoe_float_helper.h"


struct matrix * new_matrix(int col_size, int row_size, int entry_range) {
    
    struct matrix *A = (struct matrix *)malloc(sizeof(struct matrix));
    A->row_size = row_size;
    A->col_size = col_size;
    //A->entry = (int**)malloc(row_size * sizeof(int*));
    A->entry = (float**)malloc(row_size * sizeof(float*));

    if(entry_range == 1) {
		for(int i = 0; i < A->row_size; ++i) {
			//A->entry[i] = (int*)calloc(col_size, sizeof(int));
			A->entry[i] = (float*)calloc(col_size, sizeof(float));
		}
    }

    else {
        for(int i = 0; i < A->row_size; ++i) {
            //A->entry[i] = (int*)malloc(col_size * sizeof(int));
            A->entry[i] = (float*)malloc(col_size * sizeof(float));
            for(int j = 0; j < col_size; ++j) {
                A->entry[i][j] = (float)(rand() % entry_range);
            }
        }
    }

    return A;
}


struct matrix * new_matrix_as_basis(int size, int entry_range) {
    
    struct matrix *A = new_matrix(size, size, entry_range);
    gram_schmidt(A);

    return A; 
}


void del_matrix(struct matrix *A) {

    for(int i = 0; i < A->row_size; ++i)
        free(A->entry[i]);
    free(A->entry);
    free(A);

    return;
}


float dot(float *u, float *v, int col_size) {
    
    float dot_prod = 0;
    for(int i = 0; i < col_size; ++i)
        dot_prod = dot_prod + (u[i] * v[i]);

    return dot_prod;
}


void project(float *u, float *v, float *r, int col_size) {
    
    float dot_uv = dot(u, v, col_size);
    float dot_uu = dot(u, u, col_size);

    for(int i = 0; i < col_size; ++i)
        r[i] = (dot_uv / dot_uu) * u[i];

    return;
}


void gram_schmidt(struct matrix *A) {

    float *r = (float*)malloc(A->col_size * sizeof(float));

    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < i; ++j) {
            project(A->entry[j], A->entry[i], r, A->col_size);
            for(int k = 0; k < A->col_size; ++k) {
                A->entry[i][k] = A->entry[i][k] - r[k];
            }
        }
    }

    free(r);

    return;
}


void lu_decomp(struct matrix *U, struct matrix *L) {

    // convert L into identity matrix
    for(int i = 0; i < L->col_size; ++i) {
        L->entry[i][i] = 1;
    }

    float factor = 0;
    // sq_dim describes the dimensions of a square matrix: sq_dim = cols = rows
    int sq_dim = U->col_size;
    // select top row in forming upper triangular matrix
    // the interator i is used as both a row and column iterator
    for(int i = 0; i < sq_dim - 1; ++i) {
        // select all rows below the target row
        for(int j = i + 1; j < U->col_size; ++j) {
            // calculate factor 
            factor = U->entry[i][j]/U->entry[i][i];
            L->entry[i][j] = factor;
            // update all elements in a row
            for(int k = 0; k < U->row_size; ++k) {
                U->entry[k][j] = U->entry[k][j] - (factor * U->entry[k][i]);
            }
        }
    }

    return;
}


void lu_solve(struct matrix *L, struct matrix *U, float *b, float *x) {

    float *y = (float*)malloc(L->col_size * sizeof(float));
    float tmp = 0;

    for(int i = 0; i < L->col_size; ++i) {
        tmp = 0;
        for(int j = 0; j < i - 1; ++j)
            tmp = L->entry[j][i] * y[j];
        y[i] = (b[i] - tmp) / L->entry[i][i];
    }

    for(int i = U->col_size - 1; i >= 0; --i) {
        tmp = 0;
        for(int j = U->col_size - 1; j > i; --j)
            tmp = U->entry[j][i] * x[j];
        x[i] = (y[i] - tmp) / U->entry[i][i];
    }

    free(y);

}


float lu_det(struct matrix *U) {

    float det = 1;
    for(int i = 0; i < U->col_size; ++i) {
        det = det * U->entry[i][i];
    }

    return det;
}


float hadamard(struct matrix *A, float det_A) {
   
    // maybe make another param struct matrix *L
    // if the user decides to pass in NULL then decompose
    // matrix A using lu_det. Otherwise compute lu_solve

    //float det = lu_det(U);
    float det_sq = det_A * det_A;
    
    float vol_sq = 1;
    for (int i = 0; i < A->col_size; i++)
        vol_sq = vol_sq * dot(A->entry[i], A->entry[i], A->col_size);

    float ratio = pow(det_sq/vol_sq, 1/(2.0 * A->col_size));

    return ratio;
}


void babai(struct matrix *L, struct matrix *U, float *w, float *x) {

    lu_solve(L, U, w, x);
    for(int i = 0; i < U->row_size; ++i) {
        for(int j = 0; j < U->col_size; ++j) { 
            x->entry[i][j] = round(x->entry[i][j]);
        }
    }

    return; 
}



