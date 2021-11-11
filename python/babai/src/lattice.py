# Author: Ratnodeep Bandyopadhyay. Copyright 2021. All rights reserved.

import numpy as np
import pdb
#from rational.py import Rational

class Lattice:
    
    # ==================== META & INST METHODS ======================
    # accept dim, target/random
    def __init__(self, dimension, entry_range):
        self.bas_mat = 0
        self.dim = dimension
        self.ran = entry_range
        print(self)


    # Print details of class
    def __repr__(self):
        return "Lattice of dim: {}\nEntries in [0, {}]\n".format(self.dim, self.ran)


    # ==================== HELPER METHODS ======================
    # PROJECT: project vector u onto vector v
    # RETURN: a vector (numpy ndarray)
    @staticmethod
    def project(u, v):
        dot_uv = np.dot(u, v)
        dot_uu = np.dot(u, u)
        return (dot_uv / dot_uu) * u


    # GEN_LIV: generates dim vectors of dimension dim
    # each vector is linearly independent from the others.
    # RETURN: returns a matrix of size (dim x dim). Columns
    # of the matrix are linearly independent from each other.
    @staticmethod
    def gen_liv(dim, entry_range, relational_entry_range):
        bas_mat = np.round(np.random.rand(dim, dim) * entry_range)
        ran_idx = int(np.round(np.random.rand(1, 1) * (dim - 1))[0])
        nbr_idx = (ran_idx + 1) % dim
        ran_val_one = np.round(np.random.rand(1, 1) * entry_range)[0]
        ran_val_two = np.round(np.random.rand(1, 1) * relational_entry_range)[0] + 1
        for i in range(0, dim):
            bas_mat[ran_idx][i] = ran_val_one
            bas_mat[nbr_idx][i] = ran_val_two
            ran_val_two = ran_val_two * 2
        return bas_mat
    

    # GRAM_SCHMIDT: use the gram-schmidt method to create
    # a given basis
    # RETURN: boolean (python True/False)
    @staticmethod
    #def gram_schmidt(dim, vary_cap):
    def gram_schmidt(matrix):
        dim = matrix.shape[0]
#        orth_matrix = zeros(dim, dim)
        for i in range(1, dim):
            for j in range(0, i):
#                pdb.set_trace()
                #vary = np.round(np.random.rand(1,1) * vary_cap)[0]
                #matrix[:,i] = matrix[:,i] - (vary * project(matrix[:,i], matrix[:,j]))
                matrix[:,i] = matrix[:,i] - (Lattice.project(matrix[:,j], matrix[:,i]))
        return matrix


    # ===================== USER METHODS =======================
    # GEN_ORTH_B
    @staticmethod
    def gen_orth_basis(dim):
        basis_matrix = gen_liv(dim) # create dim linearly independent vectors
        bas_mat_orth = gram_schmidt(basis_matrix, dim) # orthogonalize the matrix
        bas_mat_appr = vary(bas_mat_orth, vary_cap) # make the basis almost orthogonal
        return


    # babai: solve the CVP using babai's algorithm and target
    # vector w and basis basis
    def babai(self, w):
        return np.round(self.linear_solve())


    # HADAMARD: compute the hadamard ratio using of the basis
    # RETURN: returns a floating point
    @staticmethod
    def hadamard(matrix):
        dim = matrix.shape[0]
        det = np.linalg.det(matrix)
        if det < 0:
            det = -det
        vol = 1.0
        for i in range(0, dim):
            vol = vol * np.linalg.norm(matrix[:,i])
#        pdb.set_trace()
        return (det/vol)**(1.0/float(dim))


    # linear_solve: solve the linear system of equations
    def linear_solve(self):
        return np.linalg.inv(self.bas_mat)
