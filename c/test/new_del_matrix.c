// Author: Ratnodeep Bandyopadhyay
// Copyright Nov 21, 2021. All rights reserved.

#include "matrix.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *argv[]) {


    struct matrix *tm = new_matrix(atoi(argv[0]), atoi(argv[1]), atoi(argv[2]));
    
    for(int i = 0; i < tm->col_size; ++i) {
        for(int j = 0; j < tm->row_size; ++j) {
            printf("%d, ", tm->entry[j][i]);
        }
        printf("\n");
    }

    del_matrix(tm);

}
