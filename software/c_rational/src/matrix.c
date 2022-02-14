// Authors: Ratnodeep Bandyopadhyay, Serena Lew
// Copyright 11/20/21. All rights reserved.

// Config
#include "../../config.h"

// Internal
#ifdef USE_RATIONAL
#include "../../matrix.h"
#include "../includes/rational.h"

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
		A->entry[i][j] = (DATA_TYPE){(1 + rand() % entry_range), (1 + rand() % entry_range)};
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
            printf("%d/%d, ", A->entry[j][i].num, A->entry[j][i].den);
        }
        printf("\n");
    }
    printf("\n");

}


DATA_TYPE dot(DATA_TYPE *u, DATA_TYPE *v, int col_size) {

    DATA_TYPE  dot_prod = {0, 0};
    DATA_TYPE  mult = {0, 0};
    for(int i = 0; i < col_size; ++i) {
        //dot_prod = dot_prod + (u[i] * v[i]);
//	printf("mult: %d/%d * %d/%d = ", u[i].num, u[i].den, v[i].num, v[i].den);
	rat_mul_rat(&u[i], &v[i], &mult);
//	printf("%d/%d\n", mult.num, mult.den);
	if (i == 0) {
	    dot_prod = mult;
	}
	else {
	    rat_add_rat(&dot_prod, &mult, &dot_prod);
	}
//	printf("dot: %d/%d dot %d/%d = %d/%d\n", dot_prod.num, dot_prod.den, mult.num, mult.den, dot_prod.num, dot_prod.den);
    }
    return dot_prod;
}


void project(DATA_TYPE  *u, DATA_TYPE  *v, DATA_TYPE  *r, int col_size) {

    DATA_TYPE  dot_uv = dot(u, v, col_size);
    DATA_TYPE  dot_uu = dot(u, u, col_size);

    DATA_TYPE div = {0, 0};
    for(int i = 0; i < col_size; ++i) {
        //r[i] = (dot_uv / dot_uu) * u[i];
//	printf("dot %d/%d / %d/%d = ", dot_uv.num, dot_uv.den, dot_uu.num, dot_uu.den);
	rat_div_rat(&dot_uv, &dot_uu, &div);
//	printf("%d/%d\nmult %d/%d * %d/%d = ", div.num, div.den, div.num, div.den, u[i].num, u[i].den);
	rat_mul_rat(&div, &u[i], &r[i]);
//	printf("%d/%d\n", r[i].num, r[i].den);
    }
    return;
}


void gram_schmidt(struct matrix *A) {

    DATA_TYPE  *r = (DATA_TYPE *)malloc(A->col_size * sizeof(DATA_TYPE ));
    DATA_TYPE  output = {0, 0};

    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < i; ++j) {
            project(A->entry[j], A->entry[i], r, A->col_size);
	    printf("project: \n%d/%d\n\n", r->num, r->den);
            for(int k = 0; k < A->col_size; ++k) {
               // A->entry[i][k] = A->entry[i][k] - r[k];
		rat_sub_rat(&A->entry[i][k], &r[k], &output);
		printf("subtract %d/%d - %d/%d = %d/%d\n", A->entry[i][k].num, A->entry[i][k].den, r[k].num, r[k].den, output.num, output.den);
		A->entry[i][k] = output;
		printf("A->entry[%d][%d] = %d/%d\n\n", i, k, A->entry[i][k].num, A->entry[i][k].den);
            }
        }
    }

/*    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < A->col_size; ++j) {
            A->entry[i][j] = round(A->entry[i][j]);
        }
    }*/

    free(r);

    return;
}


void lu_decomp(struct matrix *U, struct matrix *L) {

    // convert L into identity matrix
    for(int i = 0; i < L->col_size; ++i) {
        L->entry[i][i].num = 1;
	L->entry[i][i].den = 1;
    }

    DATA_TYPE  factor = {0, 0};
    DATA_TYPE  mult = {0, 0};
    // sq_dim describes the dimensions of a square matrix: sq_dim = cols = rows
    int sq_dim = U->col_size;
    // select top row in forming upper triangular matrix
    // the interator i is used as both a row and column iterator
    for(int i = 0; i < sq_dim - 1; ++i) {
        // select all rows below the target row
        for(int j = i + 1; j < U->col_size; ++j) {
            // calculate factor
            //factor = U->entry[i][j]/U->entry[i][i];
            // L->entry[i][j] = factor;
            rat_div_rat(&U->entry[i][j], &U->entry[i][i], &factor);
//	    printf("U[%d][%d] / U[%d][%d] = %d/%d / %d/%d = %d/%d\n", i, j, i, i, U->entry[i][j].num, U->entry[i][j].den, U->entry[i][i].num, U->entry[i][i].den, factor.num, factor.den);
	    L->entry[i][j] = factor;
//	    printf("L[%d][%d] = factor = %d/%d\n\n", i, j, L->entry[i][j].num, L->entry[i][j].den);
            // update all elements in a row
            for(int k = 0; k < U->row_size; ++k) {
               //U->entry[k][j] = U->entry[k][j] - (factor * U->entry[k][i]);
                rat_mul_rat(&factor, &U->entry[k][i], &mult);
//		printf("factor * U[%d][%d] = %d/%d * %d/%d = %d/%d\n", k, i, factor.num, factor.den, U->entry[k][i].num, U->entry[k][i].den, mult.num, mult.den);
//	        printf("U[%d][%d] - mult = %d/%d - %d/%d = ", k, j, U->entry[k][j].num, U->entry[k][j].den, mult.num, mult.den);
                rat_sub_rat(&U->entry[k][j], &mult, &U->entry[k][j]);
//	        printf("%d/%d\n\n", U->entry[k][j].num, U->entry[k][j].den);
            }
        }
    }

    return;
}


void lu_solve(struct matrix *L, struct matrix *U, DATA_TYPE  *b, DATA_TYPE  *x) {

    DATA_TYPE  *y = (DATA_TYPE *)malloc(L->col_size * sizeof(DATA_TYPE ));
    DATA_TYPE  tmp = {0, 0}; 
    DATA_TYPE  mult = {0, 0};

    for(int i = 0; i < L->col_size; ++i) {
        tmp.num = 0;
	tmp.den = 0;
//printf("tmp = 0\n");
        for(int j = 0; j < i; ++j) {
            //tmp += L->entry[j][i] * y[j];
            rat_mul_rat(&L->entry[j][i], &y[j], &mult);
//printf("mult = L%d%d * y%d = %d/%d * %d/%d = %d/%d\n", j, i, i, L->entry[j][i].num, L->entry[j][i].den, y[j].num, y[j].den, mult.num, mult.den);
//printf("tmp = tmp + mult = %d/%d + above = ", tmp.num, tmp.den, mult.num, mult.den);
            if (tmp.num == 0 && tmp.den == 0) {
		tmp = mult;
	    }
	    else {
		rat_add_rat(&tmp, &mult, &tmp);
//printf("%d/%d\n", tmp.num, tmp.den);
	    }
//printf("tmp + mult = %d/%d\n", tmp.num, tmp.den);
        }
        //y[i] = (b[i] - tmp) / L->entry[i][i];
//printf("b%d - tmp = %d/%d - %d/%d = ", i, b[i].num, b[i].den, tmp.num, tmp.den);
	if (tmp.num == 0 && tmp.den == 0) {
	    tmp.num = b[i].num;
	    tmp.den = b[i].den;
	}
	else {
	    rat_sub_rat(&b[i], &tmp, &tmp);
	}
//printf("%d/%d\n", tmp.num, tmp.den);
	rat_div_rat(&tmp, &L->entry[i][i], &y[i]);
//printf("y%d = tmp / L%d%d = above / %d/%d = %d/%d\n\n", i, i, i, L->entry[i][i].num, L->entry[i][i].den, y[i].num, y[i].den);
    }

    for(int i = U->col_size - 1; i >= 0; --i) {
        tmp.num = 0;
	tmp.den = 0;
        for(int j = i + 1; j < U->col_size; ++j) {
            //tmp += U->entry[j][i] * x[j];
            rat_mul_rat(&U->entry[j][i], &x[j], &mult);
//printf("mult = U%d%d * x%d = %d/%d * %d/%d = %d/%d\n", j, i, j, U->entry[j][i].num, U->entry[j][i].den, x[j].num, x[j].den, mult.num, mult.den);
	    if (tmp.num == 0 && tmp.den == 0) {
		tmp = mult;
	    }
	    else {
//printf("tmp = tmp + mult = %d/%d + %d/%d = ", tmp.num, tmp.den, mult.num, mult.den);
		rat_add_rat(&tmp, &mult, &tmp);
//printf("%d/%d\n", tmp.num, tmp.den);
	    }
        }
        //x[i] = (y[i] - tmp) / U->entry[i][i];
//printf("tmp = y%d - tmp = %d/%d - %d/%d = ", i, y[i].num, y[i].den, tmp.num, tmp.den);
	if (tmp.num == 0 && tmp.den == 0) {
	    tmp = y[i];
	}
	else {
            rat_sub_rat(&y[i], &tmp, &tmp);
	}
//printf("%d/%d\n", tmp.num, tmp.den);
	rat_div_rat(&tmp, &U->entry[i][i], &x[i]);
//printf("x%d = tmp + U%d%d = %d/%d / %d/%d  %d/%d\n\n", i, i, i, tmp.num, tmp.den, U->entry[i][i].num, U->entry[i][i].den, x[i].num, x[i].den);
    }

    free(y);

    return;
}


DATA_TYPE lu_det(struct matrix *U) {

    DATA_TYPE  det = {1, 1};
    for(int i = 0; i < U->col_size; ++i) {
        //det = det * U->entry[i][i];
        rat_mul_rat(&det, &U->entry[i][i], &det);
    }

    return det;
}


DATA_TYPE hadamard(struct matrix *A, DATA_TYPE  det_A) {

    // maybe make another param struct matrix *L
    // if the user decides to pass in NULL then decompose
    // matrix A using lu_det. Otherwise compute lu_solve

    //DATA_TYPE  det = lu_det(U);
    //DATA_TYPE  det_sq = det_A * det_A;
    DATA_TYPE  det_sq = {0, 0};
    rat_mul_rat(&det_A, &det_A, &det_sq);
//printf("det_sq = det_A * det_A = %d/%d * itself = %d/%d\n", det_A.num, det_A.den, det_sq.num, det_sq.den);

    DATA_TYPE  vol_sq = {1, 1};
    DATA_TYPE  temp = {0, 0};

    for (int i = 0; i < A->col_size; i++) {
        //vol_sq = vol_sq * dot(A->entry[i], A->entry[i], A->col_size);
	temp = dot(A->entry[i], A->entry[i], A->col_size);
//printf("vol_sq = vol_sq * temp = %d/%d * %d/%d = ", vol_sq.num, vol_sq.den, temp.num, temp.den);
	rat_mul_rat(&vol_sq, &temp, &vol_sq);
//printf("%d/%d\n", vol_sq.num, vol_sq.den);
    }

    //DATA_TYPE  ratio = pow(det_sq/vol_sq, 1/(2.0 * A->col_size));
    DATA_TYPE  ratio = {0, 0};

    float p_var = 1/(2.0 * A->col_size);
    det_sq.num = pow(det_sq.num, p_var);
    det_sq.den = pow(det_sq.den, p_var);
    vol_sq.num = pow(vol_sq.num, p_var);
    vol_sq.den = pow(vol_sq.den, p_var);
    rat_div_rat(&det_sq, &vol_sq, &ratio);
//printf("det_sq^p = %d/%d\n", det_sq.num, det_sq.den);
//printf("vol_sq^p = %d.%d\n", vol_sq.num, vol_sq.den);
//printf("ratio: det / vol = %d/%d\n\n", ratio.num, ratio.den);

    return ratio;
}


void babai(struct matrix *L, struct matrix *U, DATA_TYPE  *w, DATA_TYPE  *x) {

    lu_solve(L, U, w, x);
/*    for(int i = 0; i < U->row_size; ++i) {
        x[i] = round(x[i]);
    }
*/
    return;
}


// MATRIX_MATRIX_MULTIPLY: Given two matrices, A_left and A_right,
// perform the following operation: A_result = A_left * A_right
// RETURN: the product matrix A_result
void mxmar(struct matrix *A_result, struct matrix *A_left, struct matrix *A_right, int r_bound) {
/*
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
    }*/
}


// CREATE_ELEMENTARY_MATRIX: given a matrix pointer A, update the entries of A
// with a lower and upper triangular matrix and multiply them to create
// a resulting matrix of determinant (+/-)1.
void unimodularize_matrix(struct matrix *A, int upper_range, int lower_range) {
/*
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
    del_matrix(TL);*/
}


#endif // USE_RATIONAL


