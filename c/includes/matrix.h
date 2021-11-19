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
// of a square matrix to 0.
// RETURN: pointer to a square matrix
struct matrix* new_matrix(int dim);


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


// HADAMARD: compute the hadamard ratio of a given matrix
float hadamard(struct matrix *);

#endif
