// Authors: Ratnodeep Bandyopadhyay
// Copyright Nov 18 2021. All rights reserved.


#ifndef FPA_MATRIX_H
#define FPA_MATRIX_H

// General
#include "../../includes/config.h"
#include "../../includes/mmem.h"

//struct matrix {
//
//    int row_size;
//    int col_size;
//
//    //int **entry;
//    DATA_TYPE **entry;
//
//};
//
//
//// NEW_MATRIX: allocates and initalizes all entries
//// of a square matrix to a random integer.
//// RETURN: pointer to a matrix of size col_size x row_size
//struct matrix * fpa_new_matrix(int col_size, int row_size, int entry_range);
//
//
//// NEW_MATRIX_AS_BASIS: create a matrix of size dim x dim with entries
//// randomly assigned between 0 and entry_range. The fpa_matrix's columns
//// will represent the basis vectors of the space Z^dim
//// RETURN: a matrix of dimension size x size
//struct matrix * new_matrix_as_basis(int size, int entry_range);
//
//
//// COPY_MATRIX: create a new matrix copying the entries of the
//// matrix A
//// RETURN: a pointer to the new the matrix copy
//struct matrix * fpa_copy_matrix(struct matrix *A);
//
//
//// DEL_MATRIX: given a fpa_matrix, deallocate all memory
//// RETURN: a bool indicating if it was successfully deallocated
//void del_fpa_matrix(struct matrix *A);
//
//
//// PRINT_MATRIX: prints the contents of matrix A
//void print_fpa_matrix(struct matrix *A);


// DOT: compute the fpa_dot product of two vectors
DATA_TYPE fpa_dot(DATA_TYPE *u, DATA_TYPE *v, int col_size);


// PROJECT: fpa_project vector u onto vector v. Return the
// projected vector through vector r.
void fpa_project(DATA_TYPE *u, DATA_TYPE *v, DATA_TYPE *r, int col_size);


// GRAM_SCHMIDT: orthogonalize a matrix A using the fpa_gram_schmidt algorithm
void fpa_gram_schmidt(struct matrix *A);


// LU_DECOMP: decomposes a matrix passed into U
// as two seperate matrices U and L. These are the upper and lower
// triangular matrices derived from the matrix passed into U.
// Returns two matrices: U & L.
void fpa_lu_decomp(struct matrix *U, struct matrix *L);


// LUP_SOLVE: using lup decomposition solve for x in Ax = b
// where A is a square fpa_matrix, and x and b are vectors.
// The result is stored in the matrix x.
void fpa_lu_solve(struct matrix *L, struct matrix *U, DATA_TYPE *b, DATA_TYPE *x);


// LUP_DET: given matrix A, compute its determinant using lup decomposition
// RETURN: the determinant
DATA_TYPE fpa_lu_det(struct matrix *U);


// HADAMARD: compute the fpa_hadamard ratio of a given fpa_matrix
// RETURN: the fpa_hadamard ratio as a DATA_TYPE.
DATA_TYPE fpa_hadamard(struct matrix *A, DATA_TYPE det_A);


// BABAI: given a target vector w and a lattice defined by the
// col space of matrix A, find the closest vector on the lattice to w
// by solving Ax = w. Quite similar to Ax = b except fpa_babai will
// round the resulting vector x.
// RETURN: the vector on the lattice closest to vector w
void fpa_babai(struct matrix *L, struct matrix *U, DATA_TYPE *w, DATA_TYPE *x);


#endif // FPA_MATRIX_H
