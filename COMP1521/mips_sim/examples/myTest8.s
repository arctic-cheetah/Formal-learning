
main:
	li $a0, -1		#load 2^16 - 1
	li $v0, 11
	syscall

	li $v0, 10
	syscall
