# Author: Ratnodeep Bandyopadhyay
# Copyright Nov 21 2021. All rights reserved.
CC = gcc

IDIR=includes
BDIR=builds
ODIR=objects
TDIR=test

FLAGS = -I$(IDIR)/

DEPS = $(IDIR)/matrix.h

#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(FLAGS)

#out: $(OBJS)
#	$(CC) -o $@ $^ $(FLAGS)

$(BDIR)/%: $(ODIR)/%.o $(DEPS)
	$(CC) -o $@ $< $(FLAGS)

$(ODIR)/%.o: $(TDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)
