// Author: Ratnodeep Bandyopadhyay Copyright. 2021

// This header defines the structure and
// minimum requirements required for Babai's Algorithm
// which uses integer inputs and integer outputs.

struct rational {
    int num;
    int den;
};

// mod_div: produces closest integer by dividing two integers
int mod_div(struct rational*);

// rat_add_rat: add two rational numbers together
// interface: (rational left of the op, rational right of the op, rational store)
void rat_add_rat(struct rational* l, struct rational* r, struct rational* s);

// rat_div_rat: multiplies two rational structures
// interface: (rational left of the op, rational right of the op, rational store)
void rat_mul_rat(struct rational* l, struct rational* r, struct rational* s);

// rat_div_rat: divides two rational structureis
// interface: (rational left of the op, rational right of the op, rational store)
void rat_div_rat(struct rational* l, struct rational* r, struct rational* s);
