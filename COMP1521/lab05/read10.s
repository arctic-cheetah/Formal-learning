# i = t0

.text
main:


loop1:
    bge $t0, 10, end1 #if (i >= 10) goto end1

    la $a0, prompt      #printf("Enter a number: ");
    li $v0, 4
    syscall

    la $t1, array
    mul $t2, $t0, 4         #scanf("%d", &numbers[i])
    add $t1, $t2, $t1
    li $v0, 5
    syscall
    sw $v0, ($t1)

    addi $t0, $t0, 1        #i +=1
    j loop1
end1:

    li $t0, 0

loop2:
    bge $t0, 10, end2 #if (i >= 10) goto end1

    la $t1, array
    mul $t2, $t0, 4
    add $t1, $t1, $t2

    li $v0, 1       #printf("%d", numbers[i])
    lw $a0, ($t1)
    syscall

    li $v0, 11      #printf("\n")
    li $a0, '\n'
    syscall

    addi $t0, $t0, 1    #i +=1
    j loop2
end2:
    li $v0, 10
    syscall


.data

array: .word 0:10 #initialise the array with 10 elements set to 0
prompt: .asciiz "Enter a number: "
