#include "matrix.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char *argv[]) {

    int col_size = atoi(argv[1]);
    int row_size = atoi(argv[2]);
    int range = atoi(argv[3]);

    struct matrix *u = new_matrix(col_size, row_size, range);
    struct matrix *v = new_matrix(col_size, row_size, range);
    
    for(int i = 0; i < col_size; ++i) {
        for(int j = 0; j < row_size; ++j) {
            printf("u(%d)  v(%d), ", u->entry[j][i], v->entry[j][i]);
        }
        printf("\n");
    }

    int prod = dot(u, v);

    printf("u.v = %d\n", prod);

    del_matrix(u);
    del_matrix(v);

    return 0;
}
