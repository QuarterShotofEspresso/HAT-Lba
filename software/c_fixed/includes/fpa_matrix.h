// Authors: Ratnodeep Bandyopadhyay
// Copyright Nov 18 2021. All rights reserved.


#ifndef MATRIX_H
#define MATRIX_H

#include "config.h"

struct fpa_matrix {

    int row_size;
    int col_size;
    
    //int **entry;
    DATA_TYPE **entry;

};

// TODO: print_fpa_matrix()
// TODO: replace new_matrix_as_basis with fpa_copy_matrix()

// NEW_MATRIX: allocates and initalizes all entries
// of a square fpa_matrix to a random integer.
// RETURN: pointer to a fpa_matrix of size col_size x row_size
struct fpa_matrix * fpa_new_matrix(int col_size, int row_size, int entry_range);


// NEW_MATRIX_AS_BASIS: create a fpa_matrix of size dim x dim with entries
// randomly assigned between 0 and entry_range. The fpa_matrix's columns
// will represent the basis vectors of the space Z^dim
// RETURN: a fpa_matrix of dimension size x size
struct fpa_matrix * new_matrix_as_basis(int size, int entry_range);


// COPY_MATRIX: create a new fpa_matrix copying the entries of the
// fpa_matrix A
// RETURN: a pointer to the new the fpa_matrix copy
struct fpa_matrix * fpa_copy_matrix(struct fpa_matrix *A);


// DEL_MATRIX: given a fpa_matrix, deallocate all memory
// RETURN: a bool indicating if it was sucesffuly deallocated
void del_fpa_matrix(struct fpa_matrix *A);


// PRINT_MATRIX: prints the contents of fpa_matrix A
void print_fpa_matrix(struct fpa_matrix *A);


// DOT: compute the fpa_dot product of two vectors
DATA_TYPE fpa_dot(DATA_TYPE *u, DATA_TYPE *v, int col_size);


// PROJECT: fpa_project vector u onto vector v. Return the
// projected vector through vector r.
void fpa_project(DATA_TYPE *u, DATA_TYPE *v, DATA_TYPE *r, int col_size);


// GRAM_SCHMIDT: orthogonalize a fpa_matrix A using the fpa_gram_schmidt algorithm
void fpa_gram_schmidt(struct fpa_matrix *A);


// LU_DECOMP: decomposes a fpa_matrix passed into U
// as two seperate matrices U and L. These are the upper and lower
// triangular matrices derived from the fpa_matrix passed into U.
// Returns two matrices: U & L.
void fpa_lu_decomp(struct fpa_matrix *U, struct fpa_matrix *L);


// LUP_SOLVE: using lup decomposition solve for x in Ax = b
// where A is a square fpa_matrix, and x and b are vectors.
// The result is stored in the fpa_matrix x.
void fpa_lu_solve(struct fpa_matrix *L, struct fpa_matrix *U, DATA_TYPE *b, DATA_TYPE *x);


// LUP_DET: given fpa_matrix A, compute its determinant using lup decomposition
// RETURN: the determinant
DATA_TYPE fpa_lu_det(struct fpa_matrix *U);


// HADAMARD: compute the fpa_hadamard ratio of a given fpa_matrix
// RETURN: the fpa_hadamard ratio as a DATA_TYPE.
DATA_TYPE fpa_hadamard(struct fpa_matrix *A, DATA_TYPE det_A);


// BABAI: given a target vector w and a lattice defined by the
// col space of fpa_matrix A, find the closest vector on the lattice to w
// by solving Ax = w. Quite similar to Ax = b except fpa_babai will
// round the resulting vector x.
// RETURN: the vector on the lattice closest to vector w
void fpa_babai(struct fpa_matrix *L, struct fpa_matrix *U, DATA_TYPE *w, DATA_TYPE *x);


#endif
