#include "../../matrix.h"
#include "../includes/rational.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(0);

    int col_size = atoi(argv[1]);
    int row_size = atoi(argv[2]);
    int range = atoi(argv[3]);

    struct matrix *A = new_matrix(col_size, row_size, range);


    printf("A before orthogonalization\n");
/*    for(int i = 0; i < A->col_size; ++i) {
        for(int j = 0; j < A->row_size; ++j) {
            printf("%d/%d, ", A->entry[j][i].num, A->entry[j][i].den);
        }
        printf("\n");
    }*/
    print_matrix(A);
    printf("\n");

    gram_schmidt(A);
    
    printf("A after orthogonalization\n");
/*    for(int i = 0; i < A->col_size; ++i) {
        for(int j = 0; j < A->row_size; ++j) {
            printf("%f, ", A->entry[j][i]);
        }
        printf("\n");
    }*/
    print_matrix(A);
    printf("\n");

//    struct rational *u = (struct rational*)malloc(col_size * sizeof(struct rational));
//    struct rational *v = (struct rational*)malloc(col_size * sizeof(struct rational));
//
//    for (int i = 0; i < col_size; i++) {
//	u[i] = A->entry[0][i];
//	v[i] = A->entry[1][i];
//	printf("u[i] = %d/%d	v[i] = %d/%d\n", u[i].num, u[i].den, v[i].num, v[i].den);
//    }
//
//    struct rational prod = dot(u, v, col_size);
//    printf("%d/%d\n", prod.num, prod.den);

    del_matrix(A);

    return 0;
}
