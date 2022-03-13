// Created by: Serena Lew
#include "../includes/rational.h"
#include "stdio.h"
#include "math.h"

void TEST_simplify(int num, int den) {
    struct rational r = {num, den};
    printf("Simplify: %d / %d\n", r.num, r.den);
    simplify(&r);
    printf("%d / %d\n\n", r.num, r.den);
}

void TEST_add(int lnum, int lden, int rnum, int rden) {
    struct rational l = {lnum, lden};
    struct rational r = {rnum, rden};
    struct rational s;

    printf("%d / %d + %d / %d\n", l.num, l.den, r.num, r.den);
    
    rat_add_rat(&l, &r, &s);

    printf("Result: %d / %d\n", s.num, s.den);
}

void TEST_sub(int lnum, int lden, int rnum, int rden) {
    struct rational l = {lnum, lden};
    struct rational r = {rnum, rden};
    struct rational s;

    printf("%d / %d - %d / %d\n", l.num, l.den, r.num, r.den);

    rat_sub_rat(&l, &r, &s);

    printf("Result: %d / %d\n", s.num, s.den);
}

void TEST_mul(int lnum, int lden, int rnum, int rden) {
    struct rational l = {lnum, lden};
    struct rational r = {rnum, rden};
    struct rational s;

    printf("%d / %d * %d / %d\n", l.num, l.den, r.num, r.den);
    
    rat_mul_rat(&l, &r, &s);
    
    printf("Result: %d / %d\n", s.num, s.den);
}

void TEST_div(int lnum, int lden, int rnum, int rden) {
    struct rational l = {lnum, lden};
    struct rational r = {rnum, rden};
    struct rational s;

    printf("%d  / %d / %d / %d\n", l.num, l.den, r.num, r.den);
 
    rat_div_rat(&l, &r, &s);

    printf("%d / %d \n", s.num, s.den);
}

int main() {
    printf("\n---- Test simplify ----\n\n");
    TEST_simplify(3945, 2124);
    TEST_simplify(2237356,1147436);
    TEST_simplify(8639573, 385);
    TEST_simplify(2967, 2345613);

    printf("\n---- Test add ----\n\n");
    TEST_add(400, 123, 4563, 162);
    TEST_add(4519385, 91902, 1212314, 189200);
    TEST_add(134567, 12, 5123413, 984);

    printf("\n---- Test sub ----\n\n");
    TEST_sub(1245, 531, 612, 56);
    TEST_sub(123512, 4556, 21663, 67542);
    TEST_sub(88, 1, 83746, 1231453);

    printf("\n---- Test mul ----\n\n");
    TEST_mul(123, 52, 62, 125);
    TEST_mul(513573, 1244, 5663, 146333);
    TEST_mul(2315, 1, 35467, 456);

    printf("\n---- Test div ----\n\n");
    TEST_div(174, 123, 563, 882);
    TEST_div(186468, 193468, 917262, 1412);
    TEST_div(1846, 567, 86524, 912);

    return 0;
}
