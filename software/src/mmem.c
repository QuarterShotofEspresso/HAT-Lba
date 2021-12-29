//
// Created by Ratnodeep Bandyopadhyay on 12/25/21.
//

// General
#include "../includes/config.h"
#include "../includes/mmem.h"

// External
#include <stdlib.h>
#include <stdio.h>

struct matrix * new_matrix(int col_size, int row_size, int entry_range) {

    struct matrix *A = (struct matrix *)malloc(sizeof(struct matrix));
    A->row_size = row_size;
    A->col_size = col_size;
    //A->entry = (int**)malloc(row_size * sizeof(int*));
    A->entry = (DATA_TYPE**)malloc(row_size * sizeof(DATA_TYPE*));

    if(entry_range == 1) {
        for(int i = 0; i < A->row_size; ++i) {
            //A->entry[i] = (int*)calloc(col_size, sizeof(int));
            A->entry[i] = (DATA_TYPE*)calloc(col_size, sizeof(DATA_TYPE));
        }
    }

    else {
        for(int i = 0; i < A->row_size; ++i) {
            //A->entry[i] = (int*)malloc(col_size * sizeof(int));
            A->entry[i] = (DATA_TYPE*)malloc(col_size * sizeof(DATA_TYPE));
            for(int j = 0; j < col_size; ++j) {
                A->entry[i][j] = (DATA_TYPE)(rand() % entry_range);
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

    return;
}


void print_matrix(struct matrix *A) {

    for(int i = 0; i < A->col_size; ++i) {
        for(int j = 0; j < A->row_size; ++j) {
            printf("%f, ", A->entry[j][i]);
        }
        printf("\n");
    }
    printf("\n");

    return;
}