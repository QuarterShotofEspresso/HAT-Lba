// Authors: Ratnodeep Bandyopadhyay
// Copyright Nov 18 2021. All rights reserved.


#ifndef MATRIX_H
#define MATRIX_H

struct matrix {

    int row_size;
    int col_size;
    
    //int **entry;
    float **entry;

};

// TODO: print_matrix()
// TODO: replace new_matrix_as_basis with copy_matrix()

// NEW_MATRIX: allocates and initalizes all entries
// of a square matrix to a random integer.
// RETURN: pointer to a matrix of size col_size x row_size
struct matrix * new_matrix(int col_size, int row_size, int entry_range);


// NEW_MATRIX_AS_BASIS: create a matrix of size dim x dim with entries
// randomly assigned between 0 and entry_range. The matrix's columns
// will represent the basis vectors of the space Z^dim
// RETURN: a matrix of dimension size x size
struct matrix * new_matrix_as_basis(int size, int entry_range);


// DEL_MATRIX: given a matrix, deallocate all memory
// RETURN: a bool indicating if it was sucesffuly deallocated
void del_matrix(struct matrix *A);


// DOT: compute the dot product of two vectors
float dot(float *u, float *v, int col_size);


// PROJECT: project vector u onto vector v. Return the 
// projected vector through vector r.
void project(float *u, float *v, float *r, int col_size);


// GRAM_SCHMIDT: orthogonalize a matrix A using the gram_schmidt algorithm
void gram_schmidt(struct matrix *A);


void lu_decomp(struct matrix *U, struct matrix *L);


// LUP_SOLVE: using lup decomposition solve for x in Ax = b
// where A is a square matrix, and x and b are vectors.
// The result is stored in the matrix x.
void lu_solve(struct matrix *L, struct matrix *U, struct matrix *b, struct matrix *x);


// LUP_DET: given matrix A, compute its determinant using lup decomposition
// RETURN: the determinant
float lu_det(struct matrix *U);


// HADAMARD: compute the hadamard ratio of a given matrix
// RETURN: the hadamard ratio as a float.
float hadamard(struct matrix *A, float det_A);


// BABAI: given a target vector w and a lattice defined by the
// col space of matrix A, find the closest vector on the lattice to w
// by solving Ax = w. Quite similar to Ax = b except babai will 
// round the resulting vector x.
// RETURN: the vector on the lattice closest to vector w
void babai(struct matrix *L, struct matrix *U, struct matrix *w, struct matrix *x);


#endif
