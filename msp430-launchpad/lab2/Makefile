TARGET=blink
SRC=blink.c
CC=msp430-gcc
CFLAGS=
LDFLAGS=
DEBUG=mspdebug

$(TARGET):$(SRC)
        $(CC) $(CFLAGS) $(LDFLAGS) -mmcu=msp430g2211 -o $@ $<
debug:
	$(DEBUG) rf2500 'prog $(TARGET)'
clean:
	rm -rf $(TARGET)
