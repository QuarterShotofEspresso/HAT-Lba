// Author: Ratnodeep Bandyopadhyay
// Copyright Nov 21, 2021. All rights reserved.

#include "fpa_matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    int col_size = atoi(argv[1]);
    int row_size = atoi(argv[2]);
    int range = atoi(argv[3]);

    printf("[%d, %d] in range(%d)\n", col_size, row_size, range);

    struct fpa_matrix *tm = fpa_new_matrix(col_size, row_size, range);
   
    //printf("tm @ %p. tm->col_size: %d. tm->row_size: %d. tm->entry @ %p\n", tm, tm->col_size, tm->row_size, tm->entry);
    //printf("tm @ %p\n", tm);

    for(int i = 0; i < tm->col_size; ++i) {
        for(int j = 0; j < tm->row_size; ++j) {
            printf("%f, ", tm->entry[j][i]);
        }
        printf("\n");
    }

    del_fpa_matrix(tm);

    return 0;
}
