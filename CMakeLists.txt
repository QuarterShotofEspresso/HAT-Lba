cmake_minimum_required(VERSION 3.21)
project(lattice C)

set(CMAKE_C_STANDARD 11)

include_directories(software/c_fixed/includes)
include_directories(software/c_float/includes)
include_directories(software/c_rational/includes)

add_executable(lattice
        software/includes/config.h
        software/c_fixed/includes/fpa.h
        software/c_fixed/includes/fpa_matrix.h
        software/c_fixed/src/fpa.c
        software/c_fixed/src/fpa_matrix.c
        software/c_fixed/test/test_babai.c
        software/c_fixed/test/test_basis.c
        software/c_fixed/test/test_decomp.c
        software/c_fixed/test/test_det.c
        software/c_fixed/test/test_dot.c
        software/c_fixed/test/test_fixed.c
        software/c_fixed/test/test_gram_schmidt.c
        software/c_fixed/test/test_malloc.c
        software/c_fixed/test/test_project.c
        software/c_fixed/test/test_solve.c
        software/c_float/includes/matrix.h
        software/c_float/src/matrix.c
        software/c_float/test/test_babai.c
        software/c_float/test/test_basis.c
        software/c_float/test/test_decomp.c
        software/c_float/test/test_det.c
        software/c_float/test/test_dot.c
        software/c_float/test/test_gram_schmidt.c
        software/c_float/test/test_malloc.c
        software/c_float/test/test_project.c
        software/c_float/test/test_solve.c
        software/c_rational/includes/matrix.h
        software/c_rational/includes/rational.h
        software/c_rational/src/matrix.c
        software/c_rational/src/rational.c
        software/c_rational/test/test_babai.c
        software/c_rational/test/test_basis.c
        software/c_rational/test/test_decomp.c
        software/c_rational/test/test_dot.c
        software/c_rational/test/test_gram_schmidt.c
        software/c_rational/test/test_malloc.c
        software/c_rational/test/test_project.c
        software/c_rational/test/test_rational.c
        software/c_rational/test/test_solve.c software/test/bulk_fixed.c software/includes/mmem.h software/src/mmem.c software/c_float/includes/ggh.h software/c_float/src/ggh.c software/c_float/test/test_transpose.c software/c_float/test/test_mxm.c software/c_float/test/test_mxv.c software/c_float/test/test_unimod.c software/c_float/test/test_gen_private.c)
