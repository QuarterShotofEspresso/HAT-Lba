#include "../../matrix.h"
#include "../includes/rational.h"
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

    struct rational *w = (struct rational *)malloc(size * sizeof(struct rational));
    struct rational *x = (struct rational *)malloc(size * sizeof(struct rational));
   
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
            printf("w[%d].num: ", i);
            scanf("%d", &w[i].num);
	    printf("w[%d].den: ", i);
	    scanf("%d", &w[i].den);
        }

        for(int i = 0; i < size; ++i)
            printf("w[%d] = %d/%d\n", i, w[i].num, w[i].den);

        // decompose and test lu_solve
printf("\n\ndecomp\n\n");
        lu_decomp(A, L);
        printf("U:\n");
        print_matrix(A);
        printf("L:\n");
        print_matrix(L);
printf("\n\nsolve\n\n"); 
       lu_solve(L, A, w, x);

        // print results
        printf("x:\n");
        for(int i = 0; i < size; ++i)
            printf("%d/%d,\n", x[i].num, x[i].den);
    }

    // deallocate memory
    del_matrix(A);
    del_matrix(L);
    free(w);
    free(x);

    return 0;
}
