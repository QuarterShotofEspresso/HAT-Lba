# Author: Ratnodeep Bandyopadhyay
# Copyright Nov 21 2021. All rights reserved.
#CC = gcc
#
#IDIR=includes
#BDIR=builds
##ODIR=objects
#TDIR=test
#SDIR=src
#
#FLAGS = -I$(IDIR)/
#
#IDEPS = $(IDIR)/matrix.h
#SDEPS = $(SDIR)/matrix.c

CC = gcc

FIX_DIR=c_fixed
FLT_DIR=c_float

FIX_IDIR=$(FIX_DIR)/includes
FIX_BDIR=$(FIX_DIR)/builds
FIX_SDIR=$(FIX_DIR)/src
FLT_IDIR=$(FLT_DIR)/includes
FLT_BDIR=$(FLT_DIR)/builds
FLT_SDIR=$(FLT_DIR)/src

DFT_IDIR=includes
DFT_SDIR=src

BDIR=builds
TDIR=test

#FLAGS = -I$(FIX_IDIR)/ -I$(FLT_IDIR)/

IDEPS = $(FIX_IDIR)/fpa_matrix.h $(FIX_IDIR)/fpa.h $(FLT_IDIR)/matrix.h $(GEN_IDIR)/*.h
SDEPS = $(FIX_SDIR)/fpa_matrix.c $(FIX_SDIR)/fpa.c $(FLT_SDIR)/matrix.c $(GEN_SDIR)/*.c

# Manual Example
# gcc -o builds/new_del_matrix test/new_del_matrix.c src/matrix.c src/qsoe_float_helper.c -Iincludes
# gcc -o builds/new_del_matrix test/new_del_matrix.c src/matrix.c -Iincludes

# build test program
# Use: make <filename_of_test>
# Example: make test_malloc
%: $(GEN_TDIR)/%.c $(SDEPS) $(IDEPS)
	$(CC) -o $(GEN_BDIR)/$@ $< $(SDEPS) $(FLAGS)


.PHONY: clean

clean:
	rm -rf builds/test_*

