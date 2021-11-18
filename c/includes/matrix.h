// Authors: Ratnodeep Bandyopadhyay
// Copyright Nov 18 2021. All rights reserved.


#ifndef MATRIX_H
#define MATRIX_H

struct matrix;

struct matrix {

    struct matrix *self;

    int col; // total number of columns
    int row; // total number of rows

    struct matrix* (*newMatrix)(int);
    bool (*delMatrix)(struct matrix *);
    struct matrix* (*newVector)(int);
    bool (*delVector)(struct matrix *);

};


// NEWMATRIX: 
struct matrix* new_matrix(int col, int row);


bool del_matrix(struct matrix *);


struct matrix* new_vector(int row);


bool del_vector(struct matrix *);


#endif
