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



int dot(struct matrix *u, struct matrix *v, int col_size) {
    
    //int dot_prod = 0;
    float dot_prod = 0;
    for(int i = 0; i < u->col_size; ++i) {
        dot_prod = dot_prod + (u->entry[0][i] * v->entry[0][i]);
    }

    return dot_prod;
}


void project(float *u, float *v, float *r, int col_size) { // assuming we are changing dot(struct matrix, struct matrix) to dot(float, float, int)
   // struct matrix *m_u = new_matrix((int)u, 1, 1);
   //struct matrix *m_v = new_matrix((int)v, 1, 1);
    
    float dot_uv = dot(u, v, col_size);
    float dot_uu = dot(u, u, col_size);
    *r = (dot_uv / dot_uu) * *u;
  
   //del_matrix(m_u);
   //del_matrix(m_v);

    return;
}


void gram_schmidt(struct matrix *A) {

    struct matrix *r = new_matrix(A->col_size, 1, 1);

    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < i; ++j) {
            project(A->entry[j], A->entry[i], r->entry[0]);
            for(int k = 0; k < A->col_size; ++k) {
                A->entry[i][k] = A->entry[i][k] - r->entry[0][k];
            }
        }
    }

    del_matrix(r);

    return;
}


void lup_solve(struct matrix *A, struct matrix *b, struct matrix *x) { }

float hadamard(struct matrix *A) {
    int dim = A->row_size;
    int det = lup_det(A);
    int det_sq = det * det;
    
    int vol_sq = 1;
    for (int i = 0; i < dim; i++) {
        vol_sq = vol_sq * dot(A->entry[i], A->entry[i], dim);
    }

    printf("det_sq = {%d}", det_sq);
    printf("vol_sq = {%d}", vol_sq);
 
    // power function
    float rt = 1;
    for (int i = 0; i < (1.0 / (2 * dim)); i++) {
        rt *= (det_sq / vol_sq);
    }   

    return rt;
}

void babai(struct matrix *A, struct matrix *w, struct matrix *x) {

    lup_solve(A, w, x);
    for(int i = 0; i < A->row_size; ++i) {
        for(int j = 0; j < A->col_size; ++j) { 
//            x->entry[i][j] = round(x->entry[i][j]);
        }
    }

    return; 
}



