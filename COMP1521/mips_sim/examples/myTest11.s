
main:

	add $t2, -3, 5

	move $a0, $t2		#load 2^16 - 1
	li $v0, 1
	syscall



	li $v0, 10
	syscall
