#!/usr/local/bin/python3

import numpy as np
from lattice import Lattice

tm = Lattice.gen_vecs(2, 10)
print(tm)
print(Lattice.hadamard(tm))
print(Lattice.mxp_hadamard(tm))
tmo = Lattice.gram_schmidt(tm, 0)
#print(tmo)
print(Lattice.hadamard(tmo))
print(Lattice.mxp_hadamard(tmo))
print(tmo)

x_1 = int(input("Enter x_1: "))
x_2 = int(input("Enter x_2: "))

while x_1 != '' or x_2 != '':
    w = np.array([[int(x_1)], [int(x_2)]])
    print(Lattice.st_babai(tmo, w))
    x_1 = input("Enter x_1: ")
    x_2 = input("Enter x_2: ")

print('Done.\n')

