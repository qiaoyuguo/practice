TARGET=boot.bin
IMG=boot.img
SRC=boot.asm
all:$(IMG)
$(TARGET): $(SRC)
	   nasm -o $@ $<
$(IMG):$(TARGET)
	dd if=$< of=$@ bs=512 count=1
	qemu -fda boot.img