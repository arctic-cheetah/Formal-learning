	
	.text
	.globl main
main:
	li $t1, 34
	li $t2, 10
	div $t1, $t2
	mfhi $t5
	mflo $t6
	
	li $v0, 10
	syscall






















