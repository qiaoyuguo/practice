SRCS +=args.c
SRCS +=backup.c
SRCS +=comments.c
SRCS +=globs.c
SRCS +=indent.c
SRCS +=io.c
SRCS +=lexi.c
SRCS +=output.c
SRCS +=parse.c
TARGET=indent

CC=gcc
CFLAGS = -g -Wall -Iinclude
LDFLAGS = #I use linux, so no libintl.so

$(TARGET):$(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o $(TARGET)

