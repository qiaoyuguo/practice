	;; Q3: make the string displayed correctly
	;; int10 document:http://www.ousob.com/ng/asm/ng6f862.php
	;; an building-OS tutorial:http://www.supernovah.com/Tutorials/index.php
	;; mode 0x13 memory:http://www.brackeen.com/vga/basics.html
[ORG 0x7c00]
	call DispStr
DispStr:
	mov ax, BootMessage
	mov bp, ax
	mov cx, 16
	mov ax, 01301h
	mov bx, 000ch
	mov dx, 0100h
	int  10h
	ret
BootMessage:	 db "Hello, OS world1"
	;; Q1: fill some dumb bytes
	;; Q2: write the boot sector endmark
	times 510 - ($ - $$) db 0
	dw 0xaa55
