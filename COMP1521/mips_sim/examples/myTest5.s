
main:
	li $a0, 127		# print ascii character number 127
	li $v0, 11
	syscall

	li $v0, 10
	syscall
