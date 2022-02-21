
void rat_sub_rat(struct rational* l, struct rational* r, struct rational* s) {
    
    if(l->den == r->den) {
        s->num = l->num - r->num;
        s->den = l->den;
    } else {
        s->num = (l->num * r->den) - (r->num * l->den);
        s->den = l->den * r->den;
    }

    return;
}
