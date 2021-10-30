// Author: Ratnodeep Bandyopadhyay Copyright. 2021
#include "rational.h"

int mod_div(struct rational* x) {
    
    int quo = x->num / x->den;
    int mod = x->num % x->den;

    if(mod >= (x->den / 2)) {
        return quo + 1;
    } else {
        return quo;
    }
}

void rat_mul_rat(struct rational* l, struct rational* r, struct rational* s) {
    s->num = l->num * r->num;
    s->den = l->den * r->den;
    return;
}

void rat_div_rat(struct rational* l, struct rational* r, struct rational* s) {
    s->num = l->num * r->den;
    s->den = l->den * r->num;
    return;
}
