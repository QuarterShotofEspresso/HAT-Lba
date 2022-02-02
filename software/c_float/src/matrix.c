// Authors: Ratnodeep Bandyopadhyay
// Copyright 11/20/21. All rights reserved.


// Config
#include "../../config.h"

// Internal
#ifdef USE_FLOATING_POINT
#include "../../matrix.h"

// External
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

struct matrix * new_matrix(int col_size, int row_size, int entry_range) {

    struct matrix *A = (struct matrix *)malloc(sizeof(struct matrix));
    A->row_size = row_size;
    A->col_size = col_size;
    A->entry = (DATA_TYPE**)malloc(row_size * sizeof(DATA_TYPE*));

    if(entry_range == 1) {
        for(int i = 0; i < A->row_size; ++i) {
            A->entry[i] = (DATA_TYPE*)calloc(col_size, sizeof(DATA_TYPE));
        }
    }

    else {
        for(int i = 0; i < A->row_size; ++i) {
            A->entry[i] = (DATA_TYPE*)malloc(col_size * sizeof(DATA_TYPE));
            for(int j = 0; j < col_size; ++j) {
                A->entry[i][j] = (DATA_TYPE)(rand() % entry_range) + 1;
            }
        }
    }

    return A;
}


struct matrix * copy_matrix(struct matrix *A) {

    struct matrix *C = new_matrix(A->col_size, A->row_size, 1);
    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < A->col_size; ++j) {
            C->entry[i][j] = A->entry[i][j];
        }
    }

    return C;
}


void del_matrix(struct matrix *A) {

    for(int i = 0; i < A->row_size; ++i)
        free(A->entry[i]);
    free(A->entry);
    free(A);

}


void print_matrix(struct matrix *A) {

    for(int i = 0; i < A->col_size; ++i) {
        for(int j = 0; j < A->row_size; ++j) {
            printf("%f, ", A->entry[j][i]);
        }
        printf("\n");
    }
    printf("\n");

}


DATA_TYPE dot(DATA_TYPE *u, DATA_TYPE *v, int col_size) {
    
    DATA_TYPE  dot_prod = 0;
    for(int i = 0; i < col_size; ++i)
        dot_prod = dot_prod + (u[i] * v[i]);

    return dot_prod;
}


void project(DATA_TYPE  *u, DATA_TYPE  *v, DATA_TYPE  *r, int col_size) {
    
    DATA_TYPE  dot_uv = dot(u, v, col_size);
    DATA_TYPE  dot_uu = dot(u, u, col_size);

    for(int i = 0; i < col_size; ++i)
        r[i] = (dot_uv / dot_uu) * u[i];

    return;
}


void gram_schmidt(struct matrix *A) {

    DATA_TYPE  *r = (DATA_TYPE *)malloc(A->col_size * sizeof(DATA_TYPE ));

    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < i; ++j) {
            project(A->entry[j], A->entry[i], r, A->col_size);
            for(int k = 0; k < A->col_size; ++k) {
                A->entry[i][k] = A->entry[i][k] - r[k];
            }
        }
    }

    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < A->col_size; ++j) {
            A->entry[i][j] = round(A->entry[i][j]);
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

    DATA_TYPE  factor = 0;
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


void lu_solve(struct matrix *L, struct matrix *U, DATA_TYPE  *b, DATA_TYPE  *x) {

    DATA_TYPE  *y = (DATA_TYPE *)malloc(L->col_size * sizeof(DATA_TYPE ));
    DATA_TYPE  tmp = 0;

    for(int i = 0; i < L->col_size; ++i) {
        tmp = 0;
        for(int j = 0; j < i; ++j)
            tmp += L->entry[j][i] * y[j];
        y[i] = (b[i] - tmp) / L->entry[i][i];
    }

    for(int i = U->col_size - 1; i >= 0; --i) {
        tmp = 0;
        for(int j = i + 1; j < U->col_size; ++j)
            tmp += U->entry[j][i] * x[j];
        x[i] = (y[i] - tmp) / U->entry[i][i];
    }

    free(y);

    return;
}


DATA_TYPE lu_det(struct matrix *U) {

    DATA_TYPE  det = 1;
    for(int i = 0; i < U->col_size; ++i) {
        det = det * U->entry[i][i];
    }

    return det;
}


DATA_TYPE hadamard(struct matrix *A, DATA_TYPE  det_A) {
   
    // maybe make another param struct matrix *L
    // if the user decides to pass in NULL then decompose
    // matrix A using lu_det. Otherwise compute lu_solve

    //DATA_TYPE  det = lu_det(U);
    DATA_TYPE  det_sq = det_A * det_A;
    
    DATA_TYPE  vol_sq = 1;
    for (int i = 0; i < A->col_size; i++)
        vol_sq = vol_sq * dot(A->entry[i], A->entry[i], A->col_size);

    DATA_TYPE  ratio = pow(det_sq/vol_sq, 1/(2.0 * A->col_size));

    return ratio;
}


void babai(struct matrix *L, struct matrix *U, DATA_TYPE  *w, DATA_TYPE  *x) {

    lu_solve(L, U, w, x);
    for(int i = 0; i < U->row_size; ++i) {
        x[i] = round(x[i]);
    }

    return; 
}


// TRANSPOSE: Given a matrix A, transpose it.
// RETURN: the transposed matrix through AT
//void transpose(struct matrix *AT, struct matrix *A) {
//    for(int i = 0; i < A->row_size; ++i) {
//        for(int j = 0; j < A->col_size; ++j) {
//            AT->entry[j][i] = A->entry[i][j];
//        }
//    }
//
//    return;
//}


// MATRIX_MATRIX_MULTIPLY: Given two matrices, A_left and A_right,
// perform the following operation: A_result = A_left * A_right
// RETURN: the product matrix A_result
void mxmar(struct matrix *A_result, struct matrix *A_left, struct matrix *A_right, int r_bound) {

    int double_r_bound = r_bound * 2;
    double prod_t = 0;

    for(int i = 0; i < A_result->row_size; ++i) {
        for(int j = 0; j < A_result->col_size; ++j) {
            prod_t = (r_bound > 1)*((rand() % double_r_bound) - r_bound);
            for(int k = 0; k < A_result->col_size; ++k) {
                prod_t += A_left->entry[k][j] * A_right->entry[i][k];
            }
            A_result->entry[i][j] += prod_t;
        }
    }
}


// VECTOR_MATRIX_MULTIPLY: given a matrix A and vector v, perform
// the following operation: r = A * v.
// RETURN: the product vector r
//void mxv(DATA_TYPE *r, struct matrix *A, DATA_TYPE *v) {
//
//    struct matrix *AT = new_matrix(A->col_size, A->row_size, 1);
//    transpose(AT, A);
//
//    for(int i = 0; i < A->row_size; ++i) {
//        r[i] = dot(v, AT->entry[i], A->col_size);
//    }
//
//    del_matrix(AT);
//
//}


// CREATE_ELEMENTARY_MATRIX: given a matrix pointer A, update the entries of A
// with a lower and upper triangular matrix and multiply them to create
// a resulting matrix of determinant (+/-)1.
void unimodularize_matrix(struct matrix *A, int upper_range, int lower_range) {

    struct matrix *TU = new_matrix(A->col_size, A->row_size, 1);
    struct matrix *TL = new_matrix(A->col_size, A->row_size, 1);

    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < A->col_size; ++j) {
            if(j < i) {
                TU->entry[i][j] = rand() % upper_range;
                TL->entry[i][j] = 0;
            } else if (j > i) {
                TU->entry[i][j] = 0;
                TL->entry[i][j] = rand() % lower_range;
            } else { // j == i
                TU->entry[i][i] = 1;
                TL->entry[i][i] = 1;
            }
        }
    }

    mxmar(A, TL, TU, 1);

    del_matrix(TU);
    del_matrix(TL);
}

#endif //USE_FLOATING_POINT