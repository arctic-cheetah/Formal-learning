
main:
	li $t0, -1
	li $t1, -1

	add $t2, $t1, $t0

	move $a0, $t2		#load 2^16 - 1
	li $v0, 1
	syscall



	li $v0, 10
	syscall
