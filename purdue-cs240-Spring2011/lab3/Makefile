CC = gcc
FILENAME_PROG1 = reverse
FILE_PROG1 = reverse.c
FILENAME_PROG2 = mygrep
FILE_PROG2 = mygrep.c

all: reverse mygrep

reverse: reverse.c
	$(CC) -g -o $(FILENAME_PROG1) $(FILE_PROG1)

mygrep: mygrep.c
	$(CC) -g -o $(FILENAME_PROG2) $(FILE_PROG2)

clean:
	rm -f *.o *.out reverse mygrep
