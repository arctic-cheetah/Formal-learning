#A program that tests the over integer flow
main:
	addi $t0, $t1, 4294967294

	li $v0, 10
	syscall
