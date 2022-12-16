SRCDIR=$(HOME)/dev/advent-of-code/src/2022/day-02
LIBDIR=$(HOME)/dev/advent-of-code/libs
OUTDIR=$(HOME)/dev/advent-of-code/builds
CC=gcc
CFLAGS=-std=c11 -pedantic -I$(LIBDIR)
WARNINGS=-Wall 
DEPS = $(LIBDIR)/read_file.h $(LIBDIRDIR)/strlib.h
OBJ = $(LIBDIR)/read_file.o $(SRCDIR)/problem1.o

%.o: %.c $(DEPS)
	$(CC) -c -o  $@ $< $(CFLAGS)

solution: $(OBJ)
	$(CC) -o $(OUTDIR)/$@ $^ $(CFLAGS)
