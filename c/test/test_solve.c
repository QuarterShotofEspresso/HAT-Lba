#include "matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    // parse args
    int size = atoi(argv[1]);
    int range = atoi(argv[2]);

    // allocate memory for matrices and vectors
    struct matrix *A = new_matrix(size, size, range);    
    struct matrix *L = new_matrix(size, size, 1);    

    float *w = (float *)malloc(size * sizeof(float));
    float *x = (float *)malloc(size * sizeof(float));
   
    // print contents of A
    printf("A before ortho:\n");
    print_matrix(A);
    gram_schmidt(A);
    printf("A after ortho:\n");
    print_matrix(A);

    char ans;
    printf("Quit? ");
    scanf("%c", &ans);
    if(ans == 'n') {
        // enter contents of w
        for(int i = 0; i < size; ++i) {
            printf("w[%d]: ", i);
            scanf("%f", &w[i]);
        }

        for(int i = 0; i < size; ++i)
            printf("w[%d] = %f\n", i, w[i]);

        // decompose and test lu_solve
        lu_decomp(A, L);
        printf("U:\n");
        print_matrix(A);
        printf("L:\n");
        print_matrix(L);
        lu_solve(L, A, w, x);

        // print results
        printf("x:\n");
        for(int i = 0; i < size; ++i)
            printf("%f,\n", x[i]);
    }

    // deallocate memory
    del_matrix(A);
    del_matrix(L);
    free(w);
    free(x);

    return 0;
}
