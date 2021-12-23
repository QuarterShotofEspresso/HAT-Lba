#include "fpa_matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "fpa.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    init_fpa_meta();

    int size = atoi(argv[1]);
    int range = atoi(argv[2]);

    struct fpa_matrix *A = fpa_new_matrix(size, size, range);
    struct fpa_matrix *L = fpa_new_matrix(size, size, 1);

    printf("A:\n");
    for(int i = 0; i < A->col_size; ++i) {
        for(int j = 0; j < A->row_size; ++j) {
            printf("%f, ", A->entry[j][i]);
        }
        printf("\n");
    }
    printf("\n");

    fpa_lu_decomp(A, L);
    
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

    del_fpa_matrix(A);
    del_fpa_matrix(L);

    return 0;
}
