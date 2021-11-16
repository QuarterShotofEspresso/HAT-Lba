includes=includes/


DEPS = rational.h
OBJS = rational.o

ODIR = build

%.o: %.c $(DEPS)
	gcc -c -o $@ $< -I$(includes)

out: $(OBJS)
	gcc -o $@ $^ -I$(includes)
