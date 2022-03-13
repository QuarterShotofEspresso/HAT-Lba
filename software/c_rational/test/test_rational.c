#include "../includes/rational.h"
#include <stdio.h>

void TEST_mod_div(int num, int den) {

    struct rational tv = {num, den};
    printf("mod_div: %d\n", mod_div(&tv));

    return;
}

int main() {

    // test sequence
    TEST_mod_div(12, 15);
    TEST_mod_div(267, 12);
    TEST_mod_div(-14, 7);
    TEST_mod_div(3214, 12);
    TEST_mod_div(3, 2);
    TEST_mod_div(14, -7);
    TEST_mod_div(-13, 7);

}
