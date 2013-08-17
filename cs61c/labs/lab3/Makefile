UNAME_S := $(shell uname -s)
CC=gcc
LD=gcc
CFLAGS=-ggdb -Wall -pedantic -std=c99
LDFLAGS=

ifeq ($(UNAME_S), Darwin)
    MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes --dsymutil=yes --suppressions=osx_vector.supp
endif

ifeq ($(UNAME_S), Linux)
    MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes
endif

VECTOR_OBJS=vector.o vector-test.o
VECTOR_PROG=vector-test

LL_OBJS=ll.o ll-test.o
LL_PROG=ll-test

PROGS=$(VECTOR_PROG) $(LL_PROG) 

all: $(PROGS)

$(VECTOR_PROG): $(VECTOR_OBJS)
	$(LD) -o $(VECTOR_PROG) $(VECTOR_OBJS) $(LDFLAGS)

$(LL_PROG): $(LL_OBJS)
	$(LD) -o $(LL_PROG) $(LL_OBJS) $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $<

vector-memcheck: $(VECTOR_PROG)
	$(MEMCHECK) ./$(VECTOR_PROG)

ll-memcheck: $(LL_PROG)
	$(MEMCHECK) ./$(LL_PROG)

clean: 
	-rm -rf core *.o *~ "#"*"#" Makefile.bak $(PROGS) *.dSYM
        
vector.c: vector.h
vector-test.c: vector.h

