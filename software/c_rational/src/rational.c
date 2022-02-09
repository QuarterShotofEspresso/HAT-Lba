// Author: Ratnodeep Bandyopadhyay Copyright. 2021
#include "../includes/rational.h"
#include <math.h>
#include <stdio.h>

int mod_div(struct rational* x) {

    // move negative to the numerator
    if(x->den < 0) {
        x->num = -x->num;
        x->den = -x->den;
    }

    int quo = x->num / x->den;
    int mod = x->num % x->den;

    if(mod >= (x->den / 2)) {
        return quo + 1;
    } else {
        return quo;
    }
}

void rat_add_rat(struct rational* l, struct rational* r, struct rational* s) {
    
    if(l->den == r->den) {
        s->num = l->num + r->num;
        s->den = l->den;
    } else {
        s->num = (l->num * r->den) + (r->num * l->den);
        s->den = l->den * r->den;
    }

    simplify(s);

    return;
}

void rat_sub_rat(struct rational* l, struct rational* r, struct rational* s) {
    
    if(l->den == r->den) {
        s->num = l->num - r->num;
        s->den = l->den;
    } else {
        s->num = (l->num * r->den) - (r->num * l->den);
        s->den = l->den * r->den;
    }

    simplify(s);

    return;
}

void rat_mul_rat(struct rational* l, struct rational* r, struct rational* s) {
    s->num = l->num * r->num;
    s->den = l->den * r->den;

//printf("%d/%d\n", s->num, s->den);

    simplify(s);
 
    return;
}

void rat_div_rat(struct rational* l, struct rational* r, struct rational* s) {
    s->num = l->num * r->den;
    s->den = l->den * r->num;

    simplify(s);

    return;
}

// Added by: Serena Lew
void simplify(struct rational *s) {
   int max = pow(2, 16);
    while (s->num > max || s->den > max) {
	printf("simplifying %d/%d\n", s->num, s->den);
	s->num = s->num / 10;
	s->den = s->den / 10;
	printf("after       %d/%d\n\n", s->num, s->den);
	if (s->den <= 0) {
	    printf("Error: denominator has reached zero!\n");
	}
    }

    return;
}
