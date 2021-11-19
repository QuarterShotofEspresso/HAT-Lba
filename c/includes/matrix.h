// Authors: Ratnodeep Bandyopadhyay
// Copyright Nov 18 2021. All rights reserved.


#ifndef MATRIX_H
#define MATRIX_H

struct matrix {

    int column_size;
    int total_columns;
    
    int **entry;

};

// NEWMATRIX: allocates and initalizes all entries
// of a square matrix to a random integer.
// RETURN: pointer to a matrix of size col_size x tot_cols
struct matrix* new_matrix(int col_size, int tot_cols, int entry_range);


// DEL_MATRIX: given a matrix, deallocate all memory
// RETURN: a bool indicating if it was sucesffuly deallocated
bool del_matrix(struct matrix *);


// DOT: compute the dot product of a matrix
int dot(struct matrix *, struct matrix *);


// PROJECT: given two vectors project one onto the other
// RETURN: the projected vector
struct matrix * project(struct matrix *, struct matrix *);


// GRAM_SCHMIDT: orthogonalize a matrix using the gram_schmidt algorithm
struct matrix * gram_schmidt(struct matrix *);


// LUP_SOLVE: using lup decomposition solve Ax = b
// where A is a square matrix, and x and b are vectors
// RETURN: the vector x
struct matrix * lup_solve(struct matrix *A, struct matrix *b);


// LUP_DET: given matrix A, compute its determinant using lup decomposition
// RETURN: the determinant
int lup_det(struct matrix *A);


// HADAMARD: compute the hadamard ratio of a given matrix
// RETURN: the hadamard ratio as a float.
float hadamard(struct matrix *);


// NEW_MATRIX_AS_BASIS: create a matrix of size dim x dim with entries
// randomly assigned between 0 and entry_range. The matrix's columns
// will represent the basis vectors of the space Z^dim
// RETURN: a matrix of size dim x dim
struct matrix * new_matrix_as_basis(int dim, int entry_range);


// BABAI: given a target vector w and a lattice defined by the
// cols of matrix A, find the closest vector on the lattice to w
// RETURN: the vector on the lattice closest to vector w
struct matrix * babai(struct matrix *A, struct matrix *w);


#endif
