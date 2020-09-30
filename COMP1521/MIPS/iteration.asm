# A program that illustrates the difference between MIPS and C
.text
.globl main
main:
	li $t0, 10 # number of iterations
	li $t1, 0 # t1 is the counter (i)
	li $t2, 17 # t2 is the variable that is incremented

loop:
	beq $t1, $t0, end # if t1 == 10, end loop
	add $t2, $t2, $t1
	addi $t1, $t1, 1
	j loop
	
end:
	li $v0, 10
	syscall
	







































