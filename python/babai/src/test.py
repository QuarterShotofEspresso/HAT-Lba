from lattice import Lattice

tm = Lattice.gen_liv(3, 10, 5)
print(tm)
print(Lattice.hadamard(tm))
Lattice.gram_schmidt(tm)
print(tm)
print(Lattice.hadamard(tm))

