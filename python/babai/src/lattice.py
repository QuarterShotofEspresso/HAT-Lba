import numpy as np

class Lattice:
    
    # ==================== META & INST METHODS ======================
    # accept dim, target/random
    def __init__(self, dimension):
        self.pri_basis = 0
        self.pri_dim = dimension


    def __repr__(self):
        return "Lattice of dim: {}".format(self.pri_dim)


    # ==================== HELPER METHODS ======================
    # project: project vector u onto vector v
    # return type: a vector (numpy ndarray)
    @classmethod
    def project(u, v):
        dot_uv = np.dot(u, v)
        dot_uu = np.dot(u, u)
        return (dot_uv / dot_uu) * u


    # gram_schmidt: use the gram-schmidt method to create
    # a basis
    # return type: boolean (python True/False)
    def gram_schmidt(self):
        for v in self.pri_basis:
            v - Lattice.project()
        

    # ===================== USER METHODS =======================
    # makebasis: generate a basis of dimension pri_dimension
    def makebasis(self):
        random_basis = np.round(np.rand(self.pri_dim, 1) * 9999)
        for i in range(1, self.pri_dim):

    # babai: solve the CVP using babai's algorithm and target
    # vector w and basis pri_basis
    def babai(self, w):
        

    # hadamard: compute the hadamard ratio using of the basis
    # pri_basis
    def hadamard(self, ):

    # linear_solve: solve the linear system of equations
    def linear_solve(self, ):
