
main:

	add $t2, -400000, 100000

	move $a0, $t2		#load 2^16 - 1
	li $v0, 1
	syscall



	li $v0, 10
	syscall
