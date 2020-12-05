#t0 = i
#t1 = last_number
#t2 = address
#Used for indexing: t3

main:


loop1:
    bge $t0, 10, end1       #if (i > 10) goto end1

    la $t2, numbers         #Fetch the position of the array
    mul $t3, $t0, 4
    add $t2, $t2, $t3

    li $v0, 5               #scanf("%d", &numbers[i]);
    syscall
    sw $v0, ($t2)

    move $t1, $v0           #last_number = numbers[i];

    addi $t0, $t0, 1
    j loop1
end1:

    li $t0, 0               #i = 0

loop2:
    bge $t0, 10, end2       #if (i > 10) goto end2

    la $t2, numbers
    mul $t3, $t0, 4
    add $t2, $t2, $t3
    lw $t2, ($t2)

    blt $t2, $t1, skip      #if (numbers[i] < last_number) goto skip

    move $a0, $t2           #printf("%d\n", numbers[i]);
    li $v0, 1
    syscall
    li $a0, '\n'
    li $v0, 11
    syscall

skip:

    addi $t0, $t0, 1
    j loop2
end2:

    li $v0, 10
    syscall

    .data
numbers: .word 0:10         #numbers[10] = {0}
