// Author: Ratnodeep Bandyopadhyay Copyright. 2021

// This header defines the structure and
// minimum requirements required for Babai's Algorithm
// which uses integer inputs and integer outputs.

// TODO: test adding function pointers to rational struct and pointer to self

struct rational {
    int num;
    int den;
};

// mod_div: produces closest integer by dividing two integers
int mod_div(struct rational* x);

// rat_add_rat: add two rational numbers together
// interface: (rational left of the op, rational right of the op, rational store)
void rat_add_rat(struct rational* s, struct rational* l, struct rational* r);

// rat_sub_rat: subtract two rational numbers
//interface: (rational left of the op, rational right of the op, rational store
void rat_sub_rat(struct rational* s, struct rational *l, struct rational* r);

// rat_div_rat: multiplies two rational structures
// interface: (rational left of the op, rational right of the op, rational store)
void rat_mul_rat(struct rational* s, struct rational* l, struct rational* r);

// rat_div_rat: divides two rational structureis
// interface: (rational left of the op, rational right of the op, rational store)
void rat_div_rat(struct rational* s, struct rational* l, struct rational* r);

// Added by: Serena Lew
// simplify: right-shift a fraction's numerator and denominator until they are both below 2^16
void simplify(struct rational *s);


