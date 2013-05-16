SRC = node.c
SRC += node.h
SRC += main.c

TARGET = linkedlist
CC = gcc
CFLAGS = -g -Wall
LDFLAGS =

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -rf *.o $(TARGET)

