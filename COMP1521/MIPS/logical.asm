
	.text
	.globl main

main:
	li $t1,	2
	li $t2, 1
	srl $t0, $t1, $t2
	li $v0, 10
	syscall

















