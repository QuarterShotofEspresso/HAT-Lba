#include "fpa_matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "fpa.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    init_fpa_meta();

    // parse args
    int size = atoi(argv[1]);
    int range = atoi(argv[2]);

    // allocate memory for matrices and vectors
    struct fpa_matrix *A = fpa_new_matrix(size, size, range);
    struct fpa_matrix *L = fpa_new_matrix(size, size, 1);

    DATA_TYPE *w = (DATA_TYPE *)malloc(size * sizeof(DATA_TYPE));
    DATA_TYPE *x = (DATA_TYPE *)malloc(size * sizeof(DATA_TYPE));
   
    // print contents of A
    printf("A before ortho:\n");
    print_fpa_matrix(A);
    fpa_gram_schmidt(A);
    printf("A after ortho:\n");
    print_fpa_matrix(A);

    char ans;
    printf("Quit? ");
    scanf("%c", &ans);
    if(ans == 'n') {
        // enter contents of w
        for(int i = 0; i < size; ++i) {
            printf("w[%d]: ", i);
            scanf("%lf", &w[i]);
        }

        for(int i = 0; i < size; ++i)
            printf("w[%d] = %f\n", i, w[i]);

        // decompose and test fpa_lu_solve
        fpa_lu_decomp(A, L);
        printf("U:\n");
        print_fpa_matrix(A);
        printf("L:\n");
        print_fpa_matrix(L);
        fpa_lu_solve(L, A, w, x);

        // print results
        printf("x:\n");
        for(int i = 0; i < size; ++i)
            printf("%.10f,\n", x[i]);
    }

    // deallocate memory
    del_fpa_matrix(A);
    del_fpa_matrix(L);
    free(w);
    free(x);

    return 0;
}
