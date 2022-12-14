#include "../../matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    // parse args
    int size = atoi(argv[1]);
    int range = atoi(argv[2]);

    // allocate memory for matrices and vectors
    struct fpa_matrix *A = fpa_new_matrix(size, size, range);
    struct fpa_matrix *L = fpa_new_matrix(size, size, 1);

    float *w = (float *)malloc(size * sizeof(float));
    float *x = (float *)malloc(size * sizeof(float));
  
    // orthogonalize A
    gram_schmidt(A);
    // print contents of A
    printf("A:\n");
    print_fpa_matrix(A);
    lu_decomp(A, L);

    char ans;
    printf("Quit? ");
    scanf("%c", &ans);
    while(ans == 'n') {
        // enter contents of w
        for(int i = 0; i < size; ++i) {
            printf("w[%d]: ", i);
            scanf("%f", &w[i]);
        }

        // decompose and test lu_solve
        babai(L, A, w, x);

        // print results
        printf("x:\n");
        for(int i = 0; i < size; ++i)
            printf("%f,\n", x[i]);
       
        // repeat ask
        fflush(stdin);
        printf("Quit? ");
        scanf("%c", &ans);
    }

    // deallocate memory
    del_fpa_matrix(A);
    del_fpa_matrix(L);
    free(w);
    free(x);

    return 0;
}
