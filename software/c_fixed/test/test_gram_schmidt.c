#include "fpa_matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "fpa.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    init_fpa_meta();

    int col_size = atoi(argv[1]);
    int row_size = atoi(argv[2]);
    int range = atoi(argv[3]);

    struct fpa_matrix *A = fpa_new_matrix(col_size, row_size, range);


    printf("A before orthogonalization\n");
    for(int i = 0; i < A->col_size; ++i) {
        for(int j = 0; j < A->row_size; ++j) {
            printf("%f, ", A->entry[j][i]);
        }
        printf("\n");
    }
    printf("\n");

    fpa_gram_schmidt(A);
    
    printf("A after orthogonalization\n");
    for(int i = 0; i < A->col_size; ++i) {
        for(int j = 0; j < A->row_size; ++j) {
            printf("%f, ", A->entry[j][i]);
        }
        printf("\n");
    }
    printf("\n");

    del_fpa_matrix(A);

    return 0;
}
