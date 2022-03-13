// Author: Ratnodeep Bandyopadhyay
// Copyright Nov 21, 2021. All rights reserved.

#include "../../matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    int col_size = atoi(argv[1]);
    int range = atoi(argv[2]);

    printf("[%d, %d] in range(%d)\n", col_size, col_size, range);

    struct matrix *tm = new_matrix_as_basis(col_size, range);
 
    //printf("tm @ %p. tm->col_size: %d. tm->row_size: %d. tm->entry @ %p\n", tm, tm->col_size, tm->row_size, tm->entry);
    //printf("tm @ %p\n", tm);

    for(int i = 0; i < tm->col_size; ++i) {
        for(int j = 0; j < tm->row_size; ++j) {
            printf("%f, ", tm->entry[j][i]);
        }
        printf("\n");
    }

    matrix(tm);

    return 0;
}
