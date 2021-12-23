#include "matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "fixed_approximation.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    init_fpa_meta();

    // parse args
    int size = atoi(argv[1]);
    int range = atoi(argv[2]);

    // allocate memory for matrices and vectors
    struct matrix *A = new_matrix(size, size, range);    
    struct matrix *L = new_matrix(size, size, 1);    

    DATA_TYPE *w = (DATA_TYPE *)malloc(size * sizeof(DATA_TYPE));
    DATA_TYPE *x = (DATA_TYPE *)malloc(size * sizeof(DATA_TYPE));
  
    // orthogonalize A
    gram_schmidt(A);
    // print contents of A
    printf("A:\n");
    print_matrix(A);
    lu_decomp(A, L);

    char ans;
    printf("Quit? ");
    scanf("%c", &ans);
    while(ans == 'n') {
        // enter contents of w
        for(int i = 0; i < size; ++i) {
            printf("w[%d]: ", i);
            scanf("%lf", &w[i]);
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
    del_matrix(A);
    del_matrix(L);
    free(w);
    free(x);

    return 0;
}
