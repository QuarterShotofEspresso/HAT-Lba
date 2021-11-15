# Author: Ratnodeep Bandyopadhyay. Copyright 2021. All rights reserved.

import numpy as np
import pdb
#from rational.py import Rational

class Lattice:
    
    # ==================== META & INST METHODS ======================
    # accept dim, target/random
    def __init__(self, dimension, entry_range):
        self.B = None
        self.dim = dimension
        print(self)


    # Print details of class
    def __repr__(self):
        return "Lattice of dim: {}\n".format(self.dim)


    # ==================== STATIC METHODS ======================
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
    def gen_liv(dim, entry_range = 999, relational_entry_range = 10):
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
    
    
    @staticmethod
    def gen_vecs(dim, entry_range = 999):
        matrix = np.round(np.random.rand(dim, dim) * entry_range)
        return matrix


    # GRAM_SCHMIDT: use the gram-schmidt method to create
    # a given basis
    # PARAMETERS: 
    #   @matrix: input matrix
    #   @vary: max percent variation from fully orthogonal (hr = 1) list of vectors
    # RETURN: Nothing
    @staticmethod
    def gram_schmidt(matrix, vary = 0):
        dim = matrix.shape[0]
        for i in range(1, dim):
            for j in range(0, i):
                vary_factor = np.round(np.random.rand(1,1))[0] + 0.5
                if vary_factor < (1.0 - vary):
                    vary_factor = 1.0 - vary
                elif vary_factor > (1.0 + vary):
                    vary_factor = 1.0 + vary
                matrix[:,i] = matrix[:,i] - (vary_factor * Lattice.project(matrix[:,j], matrix[:,i]))
        return np.round(matrix)


    # BABAI: solve the CVP using babai's algorithm and target
    # vector w and basis basis
    # RETURN: closest vector on the lattice
    @staticmethod
    def st_babai(A, w):
        t = np.linalg.solve(A, w)
        return np.round(t)


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
            norm = np.linalg.norm(matrix[:,i])
            vol = vol * norm 
            if norm == 0:
                print(matrix[:,i])
        ratio = det/vol
        hadamard_ratio = ratio**(1.0/dim)
        return hadamard_ratio


    # ===================== CLASS METHODS =======================
    # GEN_INT_LATTICE: generate an integer lattice given the dimension
    def gen_int_lattice(self, entry_range = 999, vary = 0):
        matrix = Lattice.gen_vecs(self.dim, entry_range) # create dim linearly independent vectors
        orth_matrix = Lattice.gram_schmidt(matrix, vary) # orthogonalize the matrix
        self.B = orth_matrix
        return


    # BABAI: solve the CVP using the matrix created in the class
    # RETURN: vector: closest to target vector w.
    def babai(self, w):
        return Lattice.st_babai(self.B, w)



