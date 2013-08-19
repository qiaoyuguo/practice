	.file	1 "lab3_ex6.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 3
	.abicalls
	.text
	.align	2
	.globl	main
	.ent	main
	.type	main, @function
main:
	.set	nomips16
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	lui	$3,%hi(source)
	lw	$5,%lo(source)($3)
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	beq	$5,$0,$L2
	nop

	lw	$7,%got(dest)($28)
	addiu	$6,$3,%lo(source)
	move	$4,$0
$L3:
	addu	$2,$7,$4
	addu	$3,$6,$4
	sw	$5,0($2)
	lw	$5,4($3)
	addiu	$4,$4,4
	bne	$5,$0,$L3
	nop

$L2:
	move	$2,$0
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.globl	source
	.data
	.align	2
	.type	source, @object
	.size	source, 28
source:
	.word	3
	.word	1
	.word	4
	.word	1
	.word	5
	.word	9
	.word	0

	.comm	dest,40,4
	.ident	"GCC: (crosstool-NG 1.17.0) 4.3.2"
