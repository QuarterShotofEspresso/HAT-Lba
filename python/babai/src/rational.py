# Author: Ratnodeep Bandyopadhyay. Copyright 2021. All rights reserved.

class Rational:

    def __init__(self, num, den):
        self.num = num
        self.den = den

    def __repr__(self):
        return "{} / {}".format(self.num, self.den)

    @staticmethod
    def mod_round(self):

        if(self.den < 0):
            self.num = -self.num
            self.den = -self.den
            
        quo = self.num/self.den
        rem = self.num % self.den

        if(rem >= self.den / 2):
            return quo + 1
        else:
            return quo

    @staticmethod
    def rat_add_rat(l, r, s):
        if(l.den != r.den):
            s.num = (l.num * r.den) + (r.num * l.den)
            s.den = l.den * r.den
        else:
            s.num = l.num + r.num
            s.den = l.den
        return

    @staticmethod
    def rat_mul_rat(l, r, s):
        s.num = l.num * r.num
        s.den = l.den * r.den
        return


    @staticmethod
    def rat_div_rat(l, r, s):
        s.num = l.num * r.den
        s.den = l.den * r.num
        return
