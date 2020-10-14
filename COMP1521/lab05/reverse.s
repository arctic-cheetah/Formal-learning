#count = t0

.text
main:

loop1:
    bge $t0, 10, end1

    li $v0, 4       #printf("Enter a number");
    la $a0, prompt
    syscall

    la $t1, array   #scanf("%d", &numbers[count])
    mul $t2, $t0, 4
    add $t1, $t2, $t1
    li $v0, 5
    syscall
    sw $v0, ($t1)

    addi $t0, $t0, 1 # count +=1
    j loop1
end1:

    li $v0, 4
    la $a0, reverse
    syscall

    li $t0, 9

loop2:
    blt $t0, 0, end2

    la $t1, array   #printf("%d", numbers[count])
    mul $t2, $t0, 4
    add $t1, $t1, $t2
    li $v0, 1
    lw $a0, ($t1)
    syscall

    li $a0, '\n'  #printf("\n")
    li $v0, 11
    syscall

    addi $t0, $t0, -1   #count -=1
    j loop2
end2:
    li $v0, 10
    syscall


.data
    array: .word 0:10 #initialise the array with 10 elements set to 0
    prompt: .asciiz "Enter a number: "
    reverse: .asciiz "Reverse order: \n"
