// Authors: Ratnodeep Bandyopadhyay
// Copyright 11/20/21. All rights reserved.

// General
#include "../../includes/config.h"
#include "../../includes/mmem.h"

// Specialized
#include "../includes/fpa.h"
#include "../includes/fpa_matrix.h"

// External
#include <stdlib.h>
#include <math.h>


//struct matrix * fpa_new_matrix(int col_size, int row_size, int entry_range) {
//
//    struct matrix *A = (struct matrix *)malloc(sizeof(struct matrix));
//    A->row_size = row_size;
//    A->col_size = col_size;
//    //A->entry = (int**)malloc(row_size * sizeof(int*));
//    A->entry = (DATA_TYPE**)malloc(row_size * sizeof(DATA_TYPE*));
//
//    if(entry_range == 1) {
//		for(int i = 0; i < A->row_size; ++i) {
//			//A->entry[i] = (int*)calloc(col_size, sizeof(int));
//			A->entry[i] = (DATA_TYPE*)calloc(col_size, sizeof(DATA_TYPE));
//		}
//    }
//
//    else {
//        for(int i = 0; i < A->row_size; ++i) {
//            //A->entry[i] = (int*)malloc(col_size * sizeof(int));
//            A->entry[i] = (DATA_TYPE*)malloc(col_size * sizeof(DATA_TYPE));
//            for(int j = 0; j < col_size; ++j) {
//                A->entry[i][j] = mtfp((DATA_TYPE)(rand() % entry_range));
//            }
//        }
//    }
//
//    return A;
//}


//struct matrix * new_matrix_as_basis(int size, int entry_range) {
//
//    struct matrix *A = fpa_new_matrix(size, size, entry_range);
//    fpa_gram_schmidt(A);
//
//    return A;
//}
//
//
//struct matrix * fpa_copy_matrix(struct matrix *A) {
//
//    struct matrix *C = fpa_new_matrix(A->col_size, A->row_size, 1);
//    for(int i = 0; i < A->row_size; ++i) {
//        for(int j = 0; j < A->col_size; ++j) {
//            C->entry[i][j] = A->entry[i][j];
//        }
//    }
//
//    return C;
//}
//
//
//void del_fpa_matrix(struct matrix *A) {
//
//    for(int i = 0; i < A->row_size; ++i)
//        free(A->entry[i]);
//    free(A->entry);
//    free(A);
//
//    return;
//}
//
//
//void print_fpa_matrix(struct matrix *A) {
//
//    for(int i = 0; i < A->col_size; ++i) {
//        for(int j = 0; j < A->row_size; ++j) {
//            printf("%f, ", A->entry[j][i]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//
//    return;
//}


DATA_TYPE fpa_dot(DATA_TYPE *u, DATA_TYPE *v, int col_size) {
    
    DATA_TYPE dot_prod = 0;
    for(int i = 0; i < col_size; ++i)
        dot_prod = mtfp(dot_prod + mtfp(u[i] * v[i]));

    return dot_prod;
}


void fpa_project(DATA_TYPE *u, DATA_TYPE *v, DATA_TYPE *r, int col_size) {
    
    DATA_TYPE dot_uv = fpa_dot(u, v, col_size);
    DATA_TYPE dot_uu = fpa_dot(u, u, col_size);

    for(int i = 0; i < col_size; ++i)
        r[i] = mtfp(mtfp(dot_uv / dot_uu) * u[i]);

    return;
}


void fpa_gram_schmidt(struct matrix *A) {

    DATA_TYPE *r = (DATA_TYPE*)malloc(A->col_size * sizeof(DATA_TYPE));

    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < i; ++j) {
            fpa_project(A->entry[j], A->entry[i], r, A->col_size);
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


void fpa_lu_decomp(struct matrix *U, struct matrix *L) {

    // convert L into identity fpa_matrix
    for(int i = 0; i < L->col_size; ++i) {
        L->entry[i][i] = 1;
    }

    DATA_TYPE factor = 0;
    // sq_dim describes the dimensions of a square fpa_matrix: sq_dim = cols = rows
    int sq_dim = U->col_size;
    // select top row in forming upper triangular fpa_matrix
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


void fpa_lu_solve(struct matrix *L, struct matrix *U, DATA_TYPE *b, DATA_TYPE *x) {

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


DATA_TYPE fpa_lu_det(struct matrix *U) {

    DATA_TYPE det = 1.0;
    for(int i = 0; i < U->col_size; ++i) {
        det = mtfp(det * U->entry[i][i]);
    }

    return det;
}


DATA_TYPE fpa_hadamard(struct matrix *A, DATA_TYPE det_A) {
   
    // maybe make another param struct matrix *L
    // if the user decides to pass in NULL then decompose
    // matrix A using fpa_lu_det. Otherwise compute fpa_lu_solve

    //DATA_TYPE det = fpa_lu_det(U);
    DATA_TYPE det_sq = det_A * det_A;
    
    DATA_TYPE vol_sq = 1;
    for (int i = 0; i < A->col_size; i++)
        vol_sq = vol_sq * fpa_dot(A->entry[i], A->entry[i], A->col_size);

    DATA_TYPE ratio = pow(det_sq/vol_sq, 1/(2.0 * A->col_size));

    return ratio;
}


void fpa_babai(struct matrix *L, struct matrix *U, DATA_TYPE *w, DATA_TYPE *x) {

    fpa_lu_solve(L, U, w, x);
    for(int i = 0; i < U->row_size; ++i) {
        x[i] = round(x[i]);
    }

    return; 
}



