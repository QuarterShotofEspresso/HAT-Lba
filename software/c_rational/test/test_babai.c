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

print_matrix(A);

    // orthogonalize A
    gram_schmidt(A);

    // print contents of A
    printf("A:\n");
    print_matrix(A);

    char ans;
    printf("Quit? ");
    scanf("%c", &ans);
    while(ans == 'n') {
        // enter contents of w
        for(int i = 0; i < size; ++i) {
            printf("w[%d].num: ", i);
            scanf("%d", &w[i].num);
	    printf("w[%d].den: ", i);
	    scanf("%d", &w[i].den);
        }

        // decompose and test lu_solve
        lu_decomp(A, L);
        babai(L, A, w, x);

        // print results
        printf("x:\n");
        for(int i = 0; i < size; ++i)
            printf("%d/%d,\n", x[i].num, x[i].den);
       
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
