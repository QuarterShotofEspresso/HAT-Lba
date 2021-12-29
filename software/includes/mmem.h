//
// Created by Ratnodeep Bandyopadhyay on 12/25/21.
//

#ifndef LATTICE_MMEM_H
#define LATTICE_MMEM_H

#include "config.h"

struct matrix {

    int row_size;
    int col_size;

    DATA_TYPE **entry;

};

// NEW_MATRIX: allocates and initalizes all entries
// of a square matrix to a random integer.
// RETURN: pointer to a matrix of size col_size x row_size
struct matrix * new_matrix(int col_size, int row_size, int entry_range);


// NEW_MATRIX_AS_BASIS: create a matrix of size dim x dim with entries
// randomly assigned between 0 and entry_range. The matrix's columns
// will represent the basis vectors of the space Z^dim
// RETURN: a matrix of dimension size x size
struct matrix * new_matrix_as_basis(int size, int entry_range);


// COPY_MATRIX: create a new matrix copying the entries of the
// matrix A
// RETURN: a pointer to the new the matrix copy
struct matrix * copy_matrix(struct matrix *A);


// DEL_MATRIX: given a matrix, deallocate all memory
// RETURN: a bool indicating if it was sucesffuly deallocated
void del_matrix(struct matrix *A);


// PRINT_MATRIX: prints the contents of matrix A
void print_matrix(struct matrix *A);


#endif //LATTICE_MMEM_H
