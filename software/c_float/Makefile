# Author: Ratnodeep Bandyopadhyay
# Copyright Nov 21 2021. All rights reserved.
CC = gcc

IDIR=includes
BDIR=builds
#ODIR=objects
TDIR=test
SDIR=src

FLAGS = -I$(IDIR)/

IDEPS = $(IDIR)/matrix.h
SDEPS = $(SDIR)/matrix.c


# Manual Example
# gcc -o builds/new_del_matrix test/new_del_matrix.c src/matrix.c src/qsoe_float_helper.c -Iincludes
# gcc -o builds/new_del_matrix test/new_del_matrix.c src/matrix.c -Iincludes

# build test program
# Use: make <filename_of_test>
# Example: make test_malloc
%: $(TDIR)/%.c $(SDEPS) $(IDEPS)
	$(CC) -o $(BDIR)/$@ $< $(SDEPS) $(FLAGS)


.PHONY: clean

clean:
	rm -rf builds/test_*

