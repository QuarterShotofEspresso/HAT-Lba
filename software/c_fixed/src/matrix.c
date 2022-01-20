// Authors: Ratnodeep Bandyopadhyay
// Copyright 11/20/21. All rights reserved.


//// Configuration ////
#include "../../config.h"

// Implementation Selector (Fixed-point Approximation)
#ifdef USE_FIXED_POINT

//// Includes ////
// General
#include "../../matrix.h"
// Specialized
#include "../includes/fpa.h"
#include "../includes/matrix.h"
// External
#include <stdlib.h>
#include <math.h>

//// Source ////
DATA_TYPE dot(DATA_TYPE *u, DATA_TYPE *v, int col_size) {
    
    DATA_TYPE dot_prod = 0;
    for(int i = 0; i < col_size; ++i)
        dot_prod = mtfp(dot_prod + mtfp(u[i] * v[i]));

    return dot_prod;
}


void project(DATA_TYPE *u, DATA_TYPE *v, DATA_TYPE *r, int col_size) {
    
    DATA_TYPE dot_uv = dot(u, v, col_size);
    DATA_TYPE dot_uu = dot(u, u, col_size);

    for(int i = 0; i < col_size; ++i)
        r[i] = mtfp(mtfp(dot_uv / dot_uu) * u[i]);

    return;
}


void gram_schmidt(struct matrix *A) {

    DATA_TYPE *r = (DATA_TYPE*)malloc(A->col_size * sizeof(DATA_TYPE));

    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < i; ++j) {
            project(A->entry[j], A->entry[i], r, A->col_size);
            for(int k = 0; k < A->col_size; ++k) {
                A->entry[i][k] = mtfp(A->entry[i][k] - r[k]);
            }
        }
    }

    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < A->col_size; ++j) {
            A->entry[i][j] = mtfp(round(A->entry[i][j]));
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

    DATA_TYPE factor = 0;
    // sq_dim describes the dimensions of a square matrix: sq_dim = cols = rows
    int sq_dim = U->col_size;
    // select top row in forming upper triangular matrix
    // the interator i is used as both a row and column iterator
    for(int i = 0; i < sq_dim - 1; ++i) {
        // select all rows below the target row
        for(int j = i + 1; j < U->col_size; ++j) {
            // calculate factor 
            factor = mtfp(U->entry[i][j]/U->entry[i][i]);
            L->entry[i][j] = factor;
            // update all elements in a row
            for(int k = 0; k < U->row_size; ++k) {
                U->entry[k][j] = mtfp(U->entry[k][j] - mtfp(factor * U->entry[k][i]));
            }
        }
    }

    return;
}


void lu_solve(struct matrix *L, struct matrix *U, DATA_TYPE *b, DATA_TYPE *x) {

    DATA_TYPE *y = (DATA_TYPE*)malloc(L->col_size * sizeof(DATA_TYPE));
    DATA_TYPE tmp;

    for(int i = 0; i < L->col_size; ++i) {
        tmp = 0.0;
        for(int j = 0; j < i; ++j)
            tmp += mtfp(L->entry[j][i] * y[j]);
        y[i] = mtfp(mtfp(b[i] - tmp) / L->entry[i][i]);
    }

    for(int i = U->col_size - 1; i >= 0; --i) {
        tmp = 0.0;
        for(int j = i + 1; j < U->col_size; ++j)
            tmp += mtfp(U->entry[j][i] * x[j]);
        x[i] = mtfp(mtfp(y[i] - tmp) / U->entry[i][i]);
    }

    free(y);

    return;
}


DATA_TYPE lu_det(struct matrix *U) {

    DATA_TYPE det = 1.0;
    for(int i = 0; i < U->col_size; ++i) {
        det = mtfp(det * U->entry[i][i]);
    }

    return det;
}


DATA_TYPE hadamard(struct matrix *A, DATA_TYPE det_A) {
   
    // maybe make another param struct matrix *L
    // if the user decides to pass in NULL then decompose
    // matrix A using lu_det. Otherwise compute lu_solve

    //DATA_TYPE det = lu_det(U);
    DATA_TYPE det_sq = det_A * det_A;
    
    DATA_TYPE vol_sq = 1;
    for (int i = 0; i < A->col_size; i++)
        vol_sq = vol_sq * dot(A->entry[i], A->entry[i], A->col_size);

    DATA_TYPE ratio = pow(det_sq/vol_sq, 1/(2.0 * A->col_size));

    return ratio;
}


void babai(struct matrix *L, struct matrix *U, DATA_TYPE *w, DATA_TYPE *x) {

    lu_solve(L, U, w, x);
    for(int i = 0; i < U->row_size; ++i) {
        x[i] = round(x[i]);
    }

    return; 
}

#endif   /* USE_FIXED_POINT */

