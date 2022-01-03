# Author: Ratnodeep Bandyopadhyay
# Copyright Nov 21 2021. All rights reserved.
CC = gcc

IDIR=includes
BDIR=builds
#ODIR=objects
TDIR=test
SDIR=src

FLAGS = -I$(IDIR)/

IDEPS = $(IDIR)/fpa_matrix.h $(IDIR)/fpa.h
SDEPS = $(SDIR)/fpa_matrix.c $(SDIR)/fpa.c


# Manual Example
# gcc -o builds/new_del_matrix test/new_del_matrix.c src/matrix.c src/qsoe_float_helper.c -Iincludes
# gcc -o builds/new_del_matrix test/new_del_matrix.c src/matrix.c -Iincludes

#all_tests: $(TDIR)/*.c $(SDEPS) $(IDEPS)
#	$(CC) -o

# build test program
# Use: make <filename_of_test>
# Example: make test_malloc
%: $(GEN_TDIR)/%.c $(SDEPS) $(IDEPS)
	$(CC) -o $(GEN_BDIR)/$@ $< $(SDEPS) $(FLAGS)


.PHONY: clean

clean:
	rm -rf builds/test_*

