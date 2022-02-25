#include "../../matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "../includes/fpa.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    init_fpa_meta();

    int size = atoi(argv[1]);
    int range = atoi(argv[2]);

    struct matrix *A = new_matrix(size, size, range);
    struct matrix *L = new_matrix(size, size, 1);

    printf("A:\n");
    for(int i = 0; i < A->col_size; ++i) {
        for(int j = 0; j < A->row_size; ++j) {
            printf("%f, ", A->entry[j][i]);
        }
        printf("\n");
    }
    printf("\n");

    lu_decomp(A, L);
    
    printf("U:\n");
    for(int i = 0; i < A->col_size; ++i) {
        for(int j = 0; j < A->row_size; ++j) {
            printf("%f, ", A->entry[j][i]);
        }
        printf("\n");
    }
    printf("\n");
    
    printf("L:\n");
    for(int i = 0; i < L->col_size; ++i) {
        for(int j = 0; j < L->row_size; ++j) {
            printf("%f, ", L->entry[j][i]);
        }
        printf("\n");
    }
    printf("\n");

    del_matrix(A);
    del_matrix(L);

    return 0;
}
