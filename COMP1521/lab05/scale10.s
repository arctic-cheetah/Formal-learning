# i = t0
#

.text
main:

loop1:
    bge $t0, 10, end1

    li $v0, 4
    la $a0, prompt  #printf("Enter a number")
    syscall

    la $t1, numbers #scanf("%d", &numbers[i])
    mul $t2, $t0, 4
    add $t1, $t1, $t2
    li $v0, 5
    syscall
    move $t3, $v0
    mul $t3, $t3, 10 #*=10
    sw $t3, ($t1)

    addi $t0, $t0, 1
    j loop1
end1:

    li $t0, 0   # i = 0

loop2:
    bge $t0, 10, end2

    la $t1, numbers #printf("%d", numbers[i])
    mul $t2, $t0, 4
    add $t1, $t2, $t1
    lw $a0, ($t1)
    li $v0, 1
    syscall

    li $a0, '\n'    #printf("\n")
    li $v0, 11
    syscall

    addi $t0, $t0, 1
    j loop2
end2:
    li $v0, 10
    syscall

.data

    numbers: .word 0:10
    prompt: .asciiz "Enter a number: "
    prompt2: .asciiz "TEST: "
