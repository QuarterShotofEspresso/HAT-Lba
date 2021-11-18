#include "qsoe_float_helper.h"

int round(float x) {

    float x_dec = x - (int)x;

    if(x_dec >= 0.5) {
        return (int)x + 1;
    } else {
        return (int)x;
    }

}

