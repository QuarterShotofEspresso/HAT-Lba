from lattice import Lattice

#tm = Lattice.gen_liv(3, 10, 5)
tm = Lattice.gen_vecs(3, 10)
#tm = Lattice.gen_vecs(5)
#print(tm)
print(Lattice.hadamard(tm))
tmo = Lattice.gram_schmidt(tm, 0)
#print(tmo)
print(Lattice.hadamard(tmo))

