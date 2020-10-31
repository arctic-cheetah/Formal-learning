
main:
	li $a0, 65535		#load 2^16 - 1
	li $v0, 1
	syscall

	li $v0, 10
	syscall
