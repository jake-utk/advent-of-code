DAY=03
NUM=2
PROBLEM=day$(DAY)problem$(NUM)

SRCDIR=src
OBJDIR=$(SRCDIR)/obj
OUTDIR=build
INCDIR=include

CC=gcc
CFLAGS=-std=c11 -pedantic -I$(INCDIR)

WARNINGS=-Wall
DEBUG=-g

_DEPS = read_file.h strlib.h hash_table.h
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

_OBJ = $(PROBLEM).o read_file.o strlib.o hash_table.o 
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))


$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

solution: $(OBJ)
	$(CC) -o $(OUTDIR)/$@ $^ $(CFLAGS)

.PHONY: debug clean

debug: $(OBJ)
	$(CC) -o $(OUTDIR)/$@ $^ $(CFLAGS) $(DEBUG)

clean:
	rm -i -f vgcore* $(OBJDIR)/*.o $(OUTDIR)/*
