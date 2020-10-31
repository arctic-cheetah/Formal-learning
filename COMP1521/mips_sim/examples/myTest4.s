#A program that tests integer underflow
main:
	addi $t0, $t1, -4294967294

	move $a0, $t0
	li $v0, 1
	syscall

	li $v0, 10
	syscall
