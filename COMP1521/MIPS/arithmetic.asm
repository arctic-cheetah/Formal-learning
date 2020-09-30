#A program that illustrates arithmetic in assembly (mips)
	.text
	.globl main
	
main:
	li $t0, 20
	li $t1, 10
	div $t0, $t1
	li $v0, 10
	syscall




































