# Author: Ratnodeep Bandyopadhyay
# Copyright Nov 21 2021. All rights reserved.

# Compiler
CC = gcc -std=c99

# Design Strategy Roots
FIX_DIR=c_fixed
FLT_DIR=c_float
RAT_DIR=c_rational

# Fixed-point Directories
FIX_IDIR=$(FIX_DIR)/includes
FIX_BDIR=$(FIX_DIR)/builds
FIX_SDIR=$(FIX_DIR)/src
FIX_TDIR=$(FIX_DIR)/test

# Floating-point Directories
#FLT_IDIR=$(FLT_DIR)/includes
FLT_BDIR=$(FLT_DIR)/builds
FLT_SDIR=$(FLT_DIR)/src
FLT_TDIR=$(FLT_DIR)/test

# Rational Directories
RAT_IDIR=$(RAT_DIR)/includes
RAT_BDIR=$(RAT_DIR)/builds
RAT_SDIR=$(RAT_DIR)/src
RAT_TDIR=$(RAT_DIR)/test

# Shared includes and src Directories
GEN_IDIR=includes
GEN_SDIR=src
GEN_BDIR=builds
GEN_TDIR=test

FLAGS = -I$(FIX_IDIR)/ -I$(FLT_IDIR)/ -I$(RAT_IDIR)/

# General Dependencies
GEN_IDEPS = ./*.h
GEN_SDEPS = $(GEN_SDIR)/*.c

# Floating-point Dependencies
FLT_IDEPS = $(FLT_IDIR)/*.h
FLT_SDEPS = $(FLT_SDIR)/*.c

FIX_IDEPS = $(FIX_IDIR)/*.h
FIX_SDEPS = $(FIX_SDIR)/*.c

RAT_IDEPS = $(RAT_IDIR)/*.h
RAT_SDEPS = $(RAT_SDIR)/*.c

IDEPS = $(RAT_IDIR)/rational.h $(FIX_IDIR)/fpa_matrix.h $(FIX_IDIR)/fpa.h $(FLT_IDIR)/matrix.h $(GEN_IDIR)/*.h
SDEPS = $(RAT_IDIR)/rational.c $(FIX_SDIR)/fpa_matrix.c $(FIX_SDIR)/fpa.c $(FLT_SDIR)/matrix.c $(GEN_SDIR)/*.c


# Manual Example
# gcc -o builds/new_del_matrix test/new_del_matrix.c src/matrix.c src/qsoe_float_helper.c -Iincludes
# gcc -o builds/new_del_matrix test/new_del_matrix.c src/matrix.c -Iincludes

#%: %.c $(SDEPS) $(IDEPS)
#	$(CC) -o $(BDIR)/$@ $< $(SDEPS) $(FLAGS)

# gcc -o c_float/builds/test_transpose c_float/test/test_transpose.c $(SDEPS)
# build test program
# Use: make <filename_of_test>
# Example: make flt_test_malloc
flt_%: $(FLT_TDIR)/%.c $(FLT_SDEPS) $(GEN_IDEPS) $(GEN_SDEPS)
	$(CC) -o $(GEN_BDIR)/$@ $< $(FLT_SDEPS) $(GEN_SDEPS) -lm

fix_%: $(FIX_TDIR)/%.c $(FIX_SDEPS) $(FIX_IDEPS) $(GEN_IDEPS) $(GEN_SDEPS)
	$(CC) -o $(GEN_BDIR)/$@ $< $(FIX_SDEPS) $(GEN_SDEPS) -lm

rat_%: $(RAT_TDIR)/%.c $(RAT_SDEPS) $(RAT_IDEPS) $(GEN_IDEPS) $(GEN_SDEPS)
	$(CC) -o $(GEN_BDIR)/$@ $< $(RAT_SDEPS) $(GEN_SDEPS) -lm

bulk_fixed: $(GEN_TDIR)/bulk_fixed.c $(IDEPS) $(SDEPS)
	$(CC) -o $(GEN_BDIR)/$@ $< $(SDEPS)


.PHONY: clean

clean:
	rm -rf builds/test_*
